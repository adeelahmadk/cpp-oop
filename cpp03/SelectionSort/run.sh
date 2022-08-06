#!/usr/bin/env bash

echo "compiling..."
mkdir -p ../build
g++ ../lib/utils.cxx ../lib/sorting.cxx SortDriver.cxx \
    -I../include \
    -o ../build/SelectionSort

../build/SelectionSort
