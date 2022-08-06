// except.h
// Exceptions for objects and containers
#ifndef _EXCEPT_H
#define _EXCEPT_H

#include <string>
#include <stdexcept>
using namespace std;

class IllegalIndexException : public out_of_range
{
public:
    IllegalIndexException()
        : out_of_range( "attempt to access an illegal index" ) {}
    IllegalIndexException( const string &msg )
        : out_of_range( msg ) {}
};

class IndexOutOfBoundException : public length_error
{
public:
    IndexOutOfBoundException()
        : length_error( "attempt to access an index out of array bounds" ) {}
    IndexOutOfBoundException( const string &msg )
        : length_error( msg ) {}
};

#endif
