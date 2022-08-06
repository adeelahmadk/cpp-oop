// read a random access (binary) file
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include "record.h"
using namespace std;

int main()
{
    int recordCount = 0;
    // open file for reading binary data
    fstream fin( "students.bin", ios::in | ios::binary );
    // handle error
    if( !fin )
    {
        cerr << "error: openning file for input failed!" << endl;
        exit(1);
    }

    recordCount = getRecordCount( fin );
    cout << "Reading " << recordCount << " record(s)..." << endl;

    // print record header
    printRecordHeader();
    for( int recordNumber = 1; recordNumber <= recordCount; recordNumber++ )
    {
        student rec = readRecord( fin, recordNumber );
        if( ! isDeletedRecord( rec ) )
            printRecord( rec ); // print the record

    }

    // close the file
    fin.close();
    return 0;
}
