#!/bin/bash

gcc -o main test.c select.c socket.c

# Running Valgrind for memory leaking
valgrind                    \
    --leak-check=full       \
    --show-leak-kinds=all   \
    --track-origins=yes     \
    --verbose               \
    --log-file=valgrind     \
    ./main
