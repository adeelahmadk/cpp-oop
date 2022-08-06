// inputs.h
#ifndef INPUTS_H
#define INPUTS_H

#include <string>
using namespace std;

// clear ostream buffer
void ignoreLine();
// read a valid integer input
int getInteger( const string & );
// read a valid float input
float getFloat( const string & );
// read a valid string input
string getString( const string &, const int );
// ask an answer in Yes or No
char askYesNo( const string & );

#endif
