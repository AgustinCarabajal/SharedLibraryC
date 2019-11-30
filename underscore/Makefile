# Makefile Common Libraries

all: 
	# Install the Shared Libraries
	
	# Compiling all .c
	gcc -Wall -fPIC -c *.c
	# Compiling all .o
	gcc -shared -Wl,-soname,libunderscore.so -o libunderscore.so *.o
	# Moving the lib to the global link route
	cp -u libunderscore.so /usr/lib
	cp -R -u ../underscore /usr/include

uninstall:
	rm -f /usr/lib/libunderscore.so
	rm -rf /usr/include/underscore

# Run
	# Add #include <underscore/FILE_NAME>
	# Compile with the flag -lunderscore