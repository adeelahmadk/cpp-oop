// CreateAndDestroy class definition.
// Member functions defined in CreateAndDestroy.cpp.
/* #include <string> */

#ifndef CREATE_H
#define CREATE_H

#include <cstddef>
class CreateAndDestroy
{
public:
    CreateAndDestroy( int, char * ); // constructor
    ~CreateAndDestroy(); // destructor
private:
    int objectID; // ID number for object
    char *message; // message describing object
    static const size_t MAXMSGLEN = 256;
}; // end class CreateAndDestroy

#endif
