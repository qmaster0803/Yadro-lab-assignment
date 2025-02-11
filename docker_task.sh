#!/bin/bash

# Build programs (quiet)
make 1> /dev/null

# Execute
./build/writer | ./build/reader
