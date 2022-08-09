// record.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include "inputs.h"
#include "record.h"

student nullStudentRecord;

// get number of student records in the file
int getRecordCount( ifstream &inFile )
{
    if( !inFile )
    {
        cerr << "error: no file attached to ifstream object!" << endl;
        exit(1);
    }

    // position get pointer
    inFile.seekg( 0, ios::end );  // 0 bytes from end of file
    // data length (bytes) in file divided by bytes per record
    int records = inFile.tellg() / sizeof( student );
    inFile.seekg( 0, ios::beg );  // reset get pointer

    return records;
} // end function getRecordCount

// get number of student records in the file
int getRecordCount( fstream &ioFile )
{
    if( !ioFile )
    {
        cerr << "error: no file attached to fstream object!" << endl;
        exit(1);
    }

    // position get pointer
    ioFile.seekg( 0, ios::end );  // 0 bytes from end of file
    // data length (bytes) in file divided by bytes per record
    int records = ioFile.tellg() / sizeof( student );
    ioFile.seekg( 0, ios::beg );  // reset get pointer

    return records;
} // end function getRecordRequest

// ask for a record number to search
int getRecordRequest( int recordCount )
{
   int request; // request from user
   stringstream ss;

   // display request options
   cout << "\nEnter a student id:\n";
   ss << "(# 1 - " << recordCount << ") ? ";

   do // input user request
   {
      request = getInteger( ss.str() );
   } while ( request < 1 || request > recordCount );

   return request;
} // end function getRecordRequest

// read a record in the file
student readRecord( fstream &inFile, int recordNumber )
{
    student rec;
    // position the get pointer
    inFile.seekg( ( recordNumber - 1 ) * sizeof( student ) );
    // read the record
    inFile.read(
            reinterpret_cast<char *>( &rec ),
            sizeof( student )
    );
    return rec;
} // end function readRecord

// print a row of field headings
void printRecordHeader()
{
    // print record header
    cout << setw(4) << "ID"
        << setw(NAME_LENGTH) << "Name"
        << setw(8) << "Result"
        << fixed << setprecision(2) << endl;
} // end function printRecordHeader

// print a record
void printRecord( student record )
{
    // print read record
    cout << setw(4) << record.id
        << setw(NAME_LENGTH) << record.name
        << setw(8) << record.score << endl;
} // end function printRecord

// update a record at a (record numbered) location
bool updateRecord( fstream &ioFile, int recordNumber )
{
    student rec;
    string name;
    float score;
    int length;

    // position the get pointer
    ioFile.seekp( ( recordNumber - 1 ) * sizeof( student ) );
    // copy recordNumber to the record's id field
    rec.id = recordNumber;

    // read name field from the user
    do
    {
        name = getString(
                "Enter name of the student: ",
                NAME_LENGTH );
    }while( name.size() < 3 );
    length = name.length();
    length = ( length < NAME_LENGTH ? length : NAME_LENGTH - 1 );
    // copy name from string object to record's name field
    name.copy(
            rec.name,
            length
        );
    rec.name[ length ] = '\0';  // null terminate the character array

    // read score filed from the user
    do
    {
        score = getFloat( string( "Enter score: " ) );
    }while( score < 0.0 || score > 100.0 );
    // copy score to the record's score field
    rec.score = score;

    // write the record
    ioFile.write(
            reinterpret_cast< char * >( &rec ),
            sizeof( student )
    );
    if( ioFile.good() )
    {
        return true;
    }

    return false;
} // end function updateRecord

// dalete a record at a (record numbered) location
bool deleteRecord( fstream &ioFile, int recordNumber )
{
    // position the get pointer
    ioFile.seekp( ( recordNumber - 1 ) * sizeof( student ) );

    cout << "Writing null record...\n";
    // write the record
    ioFile.write(
            reinterpret_cast< char * >( &nullStudentRecord ),
            sizeof( student )
    );
    if( ioFile.good() )
    {
        return true;
    }

    return false;
} // end function deleteRecord

// check if a record is deleted
bool isDeletedRecord( student rec )
{
    // check if the record is null
    return ( rec.id == 0 && string( rec.name ) == "" && rec.score == 0.00 );
} // end function isDeletedRecord
