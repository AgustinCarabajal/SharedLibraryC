#include "select.h"

void _select(int lsocket, void (*func)(), int backlog) {
    int opt = TRUE;
    int addrlen, new_socket, client_socket[MAX_CLIENTS], activity, i, valread, sd;
	int max_sd;
    struct sockaddr_in address;
    char *buffer;
     
    // Set of socket descriptors
    fd_set readfds;
 
    // Initialise all client_socket[] to 0 so not checked
    for (i = 0; i < MAX_CLIENTS; i++) {
        client_socket[i] = 0;
    }
	
    // Try to specify maximum of n pending connections for the master socket
    if (listen(lsocket, backlog) < 0) {
        perror("[UScore Lib Error] -listen");
        exit(EXIT_FAILURE);
    }
     
    // Accept the incoming connection
    addrlen = sizeof(address);
    puts("[UScore Lib Info]: Waiting for connections ...");
    
	while(TRUE) {
        // Clear the socket set
        FD_ZERO(&readfds);
 
        // Add master socket to set
        FD_SET(lsocket, &readfds);
        max_sd = lsocket;
		
        // Add child sockets to set
        for ( i = 0 ; i < MAX_CLIENTS ; i++) {
            // Socket descriptor
			sd = client_socket[i];
            
			// If valid socket descriptor then add to read list
			if(sd > 0) FD_SET( sd, &readfds);
            
            // Highest file descriptor number, need it for the select function
            if(sd > max_sd) max_sd = sd;
        }
 
        // Wait for an activity on one of the sockets, timeout is NULL, so wait indefinitely
        activity = select( max_sd + 1, &readfds, NULL, NULL, NULL);
   
        if ((activity < 0) && (errno != EINTR)) {
            printf("[UScore Lib Error] -select");
        }

        // If something happened on the master socket, then its an incoming connection
        if (FD_ISSET(lsocket, &readfds)) {
            if ((new_socket = accept(lsocket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                perror("[UScore Lib Error] -accept");
                exit(EXIT_FAILURE);
            }

            // Inform user of socket number - used in send and receive commands
            printf("New connection, socket fd is %d, ip is : %s, port : %d \n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            // Add new socket to array of sockets
            for (i = 0; i < MAX_CLIENTS; i++) {
                // If position is empty
				if( client_socket[i] == 0 ) {
                    client_socket[i] = new_socket;
					break;
                }
            }
        }
         
        // Else its some IO operation on some other socket :)
        for (i = 0; i < MAX_CLIENTS; i++) 
        {
            sd = client_socket[i];

            if (FD_ISSET( sd, &readfds)){
                buffer = malloc(1024);

                if ((valread = read( sd, buffer, 1024)) <= 0) {

                    // Connection lost
                    free(buffer);
                    printf("[UScore Lib Info]: Client [%d] disconnected\n", sd);
                        
                    // Close the socket and mark as 0 in list for reuse
                    close( sd );
                    client_socket[i] = 0;
                } else {

                    // Calling external function with the current file descriptor and the message
                    func(sd, buffer);
                    free(buffer);
                }
            }
        }
    }

    FD_ZERO(&readfds);
}
