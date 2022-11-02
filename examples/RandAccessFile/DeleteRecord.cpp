// delete a record from a random access (binary) file
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
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
            << "To delete a record";
        // ask for the record number
        searchKey = getRecordRequest( recordCount );
        rec = readRecord( fio, searchKey );
        if( !isDeletedRecord(rec) )
        {
            cout << "\nRecord you are about to delete: " << endl;
            printRecordHeader();
            // print the current status of the record
            rec.print();

            cout << endl;
            // ask a yes/no question
            choice = askYesNo(
                        string( "Sure want to DELETE this record?" )
                    );

            if( choice == 'y' || choice == 'Y' )
            {
                // delete the record
                if( deleteRecord( fio, searchKey ) )
                {
                    cout << "Record deleted successfully!\n";
                }
                else
                {
                    cerr << "error: writing to the file failed!" << endl;
                }
            }
        }
        else
        {
            cout << "The requested record is already deleted!" << endl;
        }

        cout << endl;
        // ask a yes/no question
        choice = askYesNo( string( "Delete another record?" ) );
    }while( choice == 'y' || choice == 'Y' );

    // close the file
    fio.close();
    return 0;
}
