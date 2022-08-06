// update a record requested by the user
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

    // open file to read and write binary data
    fstream fio( "students.bin", ios::in | ios::out | ios::binary );

    // handle error
    if( !fio )
    {
        cerr << "error: openning file failed!" << endl;
        exit(1);
    }

    // get record count
    recordCount = getRecordCount( fio );
    do
    {
        cout << "Total " << recordCount
            << " record(s) in the file.\n"
            << "To update a record";
        // ask for the record number
        searchKey = getRecordRequest( recordCount );
        cout << "Record you are about to change:" << endl;

        printRecordHeader();
        // print the current status of the record
        printRecord( readRecord( fio, searchKey ) );

        cout << endl;
        // ask a yes/no question
        choice = askYesNo( string( "Sure want to UPDATE this record?" ) );

        if( choice == 'y' || choice == 'Y' )
        {
            // update the record according to the user input
            if( updateRecord( fio, searchKey ) )
            {
                cout << "Record after update:\n";
                // print updated record
                printRecord( readRecord( fio, searchKey ) );
            }
            else
            {
                cerr << "error: writing to the file failed!" << endl;
            }
        }

        cout << endl;
        // ask a yes/no question
        choice = askYesNo( string( "Update another record?" ) );
        cout << endl;
    }while( choice == 'y' || choice == 'Y' );

    // close the file
    fio.close();
    return 0;
} // end main
