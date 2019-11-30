#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#include "socket.h"

#define TRUE   1
#define FALSE  0
#define PORT 8888

int main(int argc , char *argv[]) {
    int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[30] , max_clients = 30 , activity, i , valread , sd;
	int max_sd;
    struct sockaddr_in address;
    char *buffer;
     
    //set of socket descriptors
    fd_set readfds;
 
    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) 
    {
        client_socket[i] = 0;
    }
    
    master_socket = _lsocket("8888");
	
    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
     
    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");
    
	while(TRUE) 
    {
        //clear the socket set
        FD_ZERO(&readfds);
 
        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;
		
        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++) 
        {
            //socket descriptor
			sd = client_socket[i];
            
			//if valid socket descriptor then add to read list
			if(sd > 0) FD_SET( sd , &readfds);
            
            //highest file descriptor number, need it for the select function
            if(sd > max_sd) max_sd = sd;
        }
 
        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
   
        if ((activity < 0) && (errno != EINTR)) {
            printf("[UScore Lib Error] -select");
        }

        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                perror("[UScore Lib Error] -accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++) {
                //if position is empty
				if( client_socket[i] == 0 ) {
                    client_socket[i] = new_socket;
					break;
                }
            }
        }
         
        //else its some IO operation on some other socket :)
        for (i = 0; i < max_clients; i++) 
        {
            sd = client_socket[i];
            if (FD_ISSET( sd , &readfds)){
                buffer = malloc(1024);
                if ((valread = read( sd , buffer, 1024)) <= 0) {
                    free(buffer);
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("[UScore Lib Info]: Client [%d] disconnected", sd);
                        
                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    client_socket[i] = 0;
                }
                    
                //Echo back the message that came in
                else
                {
                    //set the string terminating NULL byte on the end of the data read
                    printf("[UScore Lib Info]: Message from %d: %s", sd, buffer);
                    free(buffer);
                }
            }
        }
    }
     
    return 0;
}
