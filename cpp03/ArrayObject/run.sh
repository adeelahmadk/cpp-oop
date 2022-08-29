#!/usr/bin/env bash

echo "compiling..."
mkdir -p ../../build
g++ ArrayDriver.cxx \
    -I../include \
    -o ../../build/ArrayObjectDriver

#../../build/ArrayObjectDriver
