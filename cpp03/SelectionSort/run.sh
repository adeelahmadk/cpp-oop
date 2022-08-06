#!/usr/bin/env bash

echo "compiling..."
g++ ../lib/utils.cxx ../lib/sorting.cxx SortDriver.cxx \
    -I../include \
    -o ../build/SelectionSort

../build/SelectionSort
