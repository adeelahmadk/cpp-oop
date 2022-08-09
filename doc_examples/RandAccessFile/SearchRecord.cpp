// search a record requested by the user
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "inputs.h"
#include "record.h"
using namespace std;

int main()
{
    int recordCount = 0,
        searchKey = 0;
    char choice = 0;
    Student rec;

    // open file for reading binary data
    fstream fin( "students.bin", ios::in | ios::binary );
    // handle error
    if( !fin )
    {
        cerr << "error: openning file for input failed!" << endl;
        exit(1);
    }

    // get record count
    recordCount = getRecordCount( fin );

    do
    {
        cout << "\nTotal " << recordCount
            << " record(s) in the file." << endl;
        // ask for the record number
        searchKey = getRecordRequest( recordCount );
        rec = readRecord( fin, searchKey );
        if( isDeletedRecord( rec ) )
        {
            cout << "\nThe requested record doesn't exist!\n" << endl;
        }
        else
        {
            printRecordHeader();
            // print the record
            rec.print();
        }
        cout << endl;
        // ask a yes/no question
        choice = askYesNo( string( "Search another record?" ) );
    }while( choice == 'y' || choice == 'Y' );

    // close the file
    fin.close();
    return 0;
} // end main
