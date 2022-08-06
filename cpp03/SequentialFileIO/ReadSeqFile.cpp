// ReadSeqFile.cpp
// Reading and printing a sequential file.
#include <iostream>
#include <fstream> // file stream
#include <iomanip>
#include <string>
#include <cstdlib> // exit function prototype
using namespace std;

void outputLine( int, const string, double ); // prototype

int main()
{
    // ifstream constructor opens the file
    ifstream inClientFile( "clients.dat", ios::in );

    // exit program if ifstream could not open file
    if ( !inClientFile )
    {
        cerr << "File could not be opened" << endl;
        exit( 1 );
    } // end if

    int account;
    string name;
    double balance;

    cout << left << setw( 10 ) << "Account" << setw( 13 )
        << "Name" << "Balance" << endl << fixed << showpoint;

    // display each record in file
    while ( inClientFile >> account >> name >> balance )
        outputLine( account, name, balance );
} // end main

// display single record from file
void outputLine( int account, const string name, double balance )
{
    cout << left << setw( 10 ) << account << setw( 13 ) << name
        << setw( 7 ) << setprecision( 2 ) << right << balance << endl;
} // end function outputLine
