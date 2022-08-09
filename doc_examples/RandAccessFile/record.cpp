// record.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "inputs.h"
#include "record.h"

// null Student object, usefull to erase
// a record in the random-access file 
Student nullStudentRecord;

// default constructor
Student::Student( int id, string name, float score ) : id_(id), score_(score)
{
    setName( name );
}

// accessor functions for Student object
Student &Student::setID( int id )
{
    id_ = id;
    return *this;
}

// set name for the Student record
Student &Student::setName( string name )
{
    int length = name.length();
    length = ( length < NAME_LENGTH ? length : NAME_LENGTH - 1 );
    // copy name from string object to record's name field
    name.copy(
            name_,
            length
        );
    name_[ length ] = '\0';  // null terminate the character array

    return *this;
}

// set score for the Student record
Student &Student::setScore( float score )
{
    score_ = score;
    return *this;
}

// print a record
void Student::print()
{
    // print read record
    cout << setw(4) << id_
        << setw(NAME_LENGTH) << name_
        << setw(8) << score_ << endl;
} // end function printRecord

// check if the record is null
bool Student::isNullRecord()
{
    // check if the record is null
    return (
            id_ == 0
        &&
            string( name_ ) == ""
        &&
            score_ == 0.00
    );
}

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
    int records = inFile.tellg() / sizeof( Student );
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
    int records = ioFile.tellg() / sizeof( Student );
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
Student readRecord( fstream &inFile, int recordNumber )
{
    Student rec;
    // position the get pointer
    inFile.seekg( ( recordNumber - 1 ) * sizeof( Student ) );
    // read the record
    inFile.read(
            reinterpret_cast<char *>( &rec ),
            sizeof( Student )
    );
    return rec;
} // end function readRecord

// print a row of field headings
void printRecordHeader()
{
    // print record header
    cout << setw(4) << "ID"
        << setw(Student::NAME_LENGTH) << "Name"
        << setw(8) << "Result"
        << fixed << setprecision(2) << endl;
} // end function printRecordHeader

// update a record at a (record numbered) location
bool updateRecord( fstream &ioFile, int recordNumber )
{
    Student rec;
    string name;
    float score;
    int length;

    // position the get pointer
    ioFile.seekp( ( recordNumber - 1 ) * sizeof( Student ) );
    // copy recordNumber to the record's id field
    rec.setID( recordNumber );

    // read name field from the user
    do
    {
        name = getString(
                "Enter name of the student: ",
                Student::NAME_LENGTH );
    }while( name.size() < 3 );
    // set record's name field to the user input
    rec.setName( name );

    // read score filed from the user
    do
    {
        score = getFloat( string( "Enter score: " ) );
    }while( score < 0.0 || score > 100.0 );
    // set the record's score field to the user input
    rec.setScore( score );

    // write the record
    ioFile.write(
            reinterpret_cast< char * >( &rec ),
            sizeof( Student )
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
    ioFile.seekp( ( recordNumber - 1 ) * sizeof( Student ) );

    cout << "Writing null record...\n";
    // write the record
    ioFile.write(
            reinterpret_cast< char * >( &nullStudentRecord ),
            sizeof( Student )
    );
    if( ioFile.good() )
    {
        return true;
    }

    return false;
} // end function deleteRecord

// check if a record is deleted
bool isDeletedRecord( Student rec )
{
    // check if the record is null
    return rec.isNullRecord();
} // end function isDeletedRecord
