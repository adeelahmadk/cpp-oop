// inputs.h
#ifndef INPUTS_H
#define INPUTS_H

#include <string>
using namespace std;

class SafeInput
{
public:
    // clear ostream buffer
    static void ignoreLine();
    // read a valid integer input
    static int getInteger( const string & );
    // read a valid float input
    static float getFloat( const string & );
    // read a valid string input
    static string getString( const string & );
};

#endif
