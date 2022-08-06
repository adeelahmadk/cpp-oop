#!/usr/bin/env bash

CXX=`which g++`
if [ $? -ne 0 ]
then
    CXX=`which clang++`
    [ $? -ne 0 ] && echo "error!" && return 1
fi

echo "my c++ compiler is: ${CXX}"
echo "compiling .cpp files..."
$CXX CreateRAFile.cpp -o CreateRAFile
$CXX inputs.cpp record.cpp ReadRAFile.cpp -o ReadRAFile
$CXX inputs.cpp record.cpp SearchRecord.cpp -o SearchRecord
$CXX inputs.cpp record.cpp UpdateRecord.cpp -o UpdateRecord
$CXX inputs.cpp record.cpp DeleteRecord.cpp -o DeleteRecord

echo
[ $? -ne 0 ] && echo "error in compiling files!" && return 1
echo "successfully compiled all .cpp files..."
return 0
