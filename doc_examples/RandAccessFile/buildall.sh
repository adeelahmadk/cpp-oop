#!/usr/bin/env bash

CWD=$(dirname `realpath $BASH_SOURCE`)
[ -f $CWD"/../../.env.sh" ] && source $CWD"/../../.env.sh"
[ -z "$BUILD_DIR" ] && BUILD_DIR="."
[ -z "$CXX" ] && \
    echo "$(basename $0): Set your C++ compiler in the CXX variable!" >& 2 && exit 1

echo "your c++ compiler is: $(basename $CXX)"
echo "compiling .cpp files..."
$CXX CreateRAFile.cpp -o $BUILD_DIR/CreateRAFile
$CXX inputs.cpp record.cpp ReadRAFile.cpp -o $BUILD_DIR/ReadRAFile
$CXX inputs.cpp record.cpp SearchRecord.cpp -o $BUILD_DIR/SearchRecord
$CXX inputs.cpp record.cpp UpdateRecord.cpp -o $BUILD_DIR/UpdateRecord
$CXX inputs.cpp record.cpp DeleteRecord.cpp -o $BUILD_DIR/DeleteRecord

[ $? -ne 0 ] && echo "error compiling files!" && exit 1
echo "successfully compiled all .cpp files..."
echo "executables palced in ${BUILD_DIR}"
