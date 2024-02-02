#!/bin/bash

# Compile server.c with the math library
gcc server.c -o server -lm

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation of server.c successful. Executable: server"
else
    echo "Compilation of server.c failed."
fi

# Compile client.c
gcc client.c -o client

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation of client.c successful. Executable: client"
else
    echo "Compilation of client.c failed."
fi

# chmod +x comile.sh

