// except.h
// Exceptions for objects and containers
#ifndef _EXCEPT_H
#define _EXCEPT_H

#include <string>
#include <stdexcept>
using namespace std;

// custom exception class definition for and IllegalIndexException
class IllegalIndexException : public out_of_range
{
public:
    IllegalIndexException()
        // pass custom message to base class constructor
        : out_of_range( "attempt to access an illegal index" ) {}
    IllegalIndexException( const string &msg )
        : out_of_range( msg ) {}
};

// custom exception class definition for and IndexOutOfBoundException
class IndexOutOfBoundException : public length_error
{
public:
    IndexOutOfBoundException()
        // pass custom message to base class constructor
        : length_error( "attempt to access an index out of array bounds" ) {}
    IndexOutOfBoundException( const string &msg )
        : length_error( msg ) {}
};

#endif
