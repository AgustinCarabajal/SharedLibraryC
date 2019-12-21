#!/bin/bash

# Test script

gcc -o main <YOUR_FILE_NAME>.c thread.c select.c socket.c -lpthread

# Running Valgrind for memory leaking
valgrind                    \
    --leak-check=full       \
    --show-leak-kinds=all   \
    --track-origins=yes     \
    --verbose               \
#    --log-file=valgrind     \
    ./main
