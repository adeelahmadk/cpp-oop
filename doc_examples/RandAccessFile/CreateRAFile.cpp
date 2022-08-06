// create a random access file
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "record.h"
using namespace std;

int main()
{
    // open file for writing binary data
    ofstream fout( "students.bin", ios::out | ios::binary );
    // handle error
    if( !fout )
    {
        cerr << "error: open file for output failed!" << endl;
        exit(1);
    }

    const int recordCount = 5;
    // initialize records
    student studentRecords[recordCount] = {
        /* this type of initialization is only
           possible at declaration time! */
        { 1, "Sqib Hameed",  83.50 },
        { 2, "Raza Farooq",  79.75 },
        { 3, "Muneeb Ahmed", 88.25 },
        { 4, "Faizan Ahmed", 73.00 },
        { 5, "Usaid Azhar",  87.67 }
    };

    for( size_t index = 0; index < recordCount; index++ )
    {
        // write a record as array of byte sized data
        fout.write(
                reinterpret_cast< char * >( &studentRecords[index] ),
                sizeof( student )  // size of record to be written
            );
    }

    fout.close();  // close file
    return 0;
}
