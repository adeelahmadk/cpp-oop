// WriteSeqFile.cpp
// Create a sequential file.
#include <iostream>
#include <string>
#include <fstream> // file stream
#include <cstdlib> // exit function prototype
using namespace std;

int main()
{
    // ofstream constructor opens file
    ofstream outClientFile( "clients.dat", ios::out | ios::app );

    // exit program if unable to create file
    if ( !outClientFile ) // overloaded ! operator
    {
        cerr << "File could not be opened" << endl;
        exit( 1 );
    } // end if

    cout << "Enter the account, name, and balance." << endl
      << "Enter end-of-file to end input.\n? ";

    int account;
    string name;
    double balance;

    // read account, name and balance from cin, then place in file
    while ( cin >> account >> name >> balance )
    {
        outClientFile << account << ' ' << name << ' ' << balance << endl;
        cout << "? ";
    } // end while
    
    cout << endl;
} // end main
