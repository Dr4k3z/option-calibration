#!/bin/bash

# Check if an argument was provided
if [ -z "$1" ]; then
    echo "Usage: ./compile_example.sh <example_main.cpp>"
    echo "Example: ./compile_example.sh src/example1_main.cpp"
    exit 1
fi

# Set the path for the chosen example
EXAMPLE_PATH="$1"

# Run cmake with the specified example
cmake -DEXAMPLE_TO_COMPILE=${EXAMPLE_PATH}
make

