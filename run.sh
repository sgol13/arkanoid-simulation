#!/bin/bash

# This script compiles and runs the simulation

if [[ ! -d "build" ]]; then
    mkdir build
fi

cd build

if [[ ! -f "Makefile" ]]; then
    cmake ..
fi

make && ./simulation