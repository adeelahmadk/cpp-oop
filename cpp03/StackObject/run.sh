#!/usr/bin/env bash

echo "compiling..."
mkdir -p ../build
g++ StackDriver.cxx \
    -I../include \
    -o ../build/StackDriver

../build/StackDriver
