# Makefile Common Libraries

all: 
	# Install the Shared Libraries
	shared_lib

shared_lib:
	# Compiling all .c
	gcc -Wall -fPIC -c *.c
	# Compiling all .o
	gcc -shared -Wl,-soname,libsnacks.so -o libsnacks.so *.o
	# Moving the lib to the global link route
	cp -u libsnacks.so /usr/lib
	cp -R -u ../snacks /usr/include

uninstall:
	rm -f /usr/lib/libsnacks.so
	rm -rf /usr/include/snacks

# Run
	# Add #include <snacks/FILE_NAME>
	# Compile with the flag -lsnacks