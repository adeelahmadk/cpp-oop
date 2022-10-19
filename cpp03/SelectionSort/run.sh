#!/usr/bin/env bash

BUILD_DIR="../build"
INC_DIR="../include"
LIB_DIR="../lib"
CC=
if [ -n `which g++` ]; then
    CC=`which g++`
elif [ -n `which clang++` ]; then
    CC=`which clang++`
else
    echo "Set your C++ compiler in $(basename $0) manually!"
    exit 1
fi

[ ! -d "$INC_DIR" ] && { echo "cpp/cxx files for included headers not found!"; exit 1; }
# create if doesn't exist
[ ! -d "$BUILD_DIR" ] && mkdir -p ../build

echo "compiling..."

$CC "$LIB_DIR/utils.cxx" "$LIB_DIR/sorting.cxx" SortDriver.cxx \
    -I"$INC_DIR" \
    -o "$BUILD_DIR/SelectionSort"

# run the binary
"$BUILD_DIR/SelectionSort"
