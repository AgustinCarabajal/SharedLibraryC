# Makefile Common Libraries

install: 
	# Install the Shared Libraries
	
	# Compiling all .c
	gcc -Wall -fPIC -c *.c
	# Compiling all .o
	gcc -shared -Wl,-soname,libchantas.so -o libchantas.so *.o
	# Moving the lib to the global link route
	cp -u libchantas.so /usr/lib
	cp -R -u ../chantas /usr/include

uninstall:
	rm -f /usr/lib/libchantas.so
	rm -rf /usr/include/chantas

update: uninstall install

# Run
	# Add #include <chantas/FILE_NAME>
	# Compile with the flag -lchantas
