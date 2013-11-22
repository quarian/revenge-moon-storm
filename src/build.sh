#!/bin/bash

# Build script for Minebombers
# Should be ruon the first time the program executes
# in a new shell - the shell has to be told where the
# shared libraries live. All kinds of things.

# Set the locaction of shared (SFML) libs
export LD_LIBRARY_PATH=./lib/
#Call make
make
