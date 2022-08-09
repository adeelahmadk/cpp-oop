// record.h
#ifndef RECORD_H
#define RECORD_H

#include <fstream>
#include <string>
using namespace std;

class Student
{
public:
    // const length for name char array
    static const int NAME_LENGTH = 30;

    // default constructor
    Student( int = 0, string = "", float = 0.0 );
    // accessor functions for Student object
    Student &setID( int id );
    int getID() const { return id_; }
    Student &setName( string name );
    string getName() const { return string( name_ ); }
    Student &setScore( float score );
    float getScore() const { return score_; }
    // print record stored in "this" object
    void print();
    // check if "this" record is deleted
    bool isNullRecord();

private:
    // alias definition for a student record
    int id_;
    char name_[NAME_LENGTH];
    float score_;
};

// get number of student records in the file
int getRecordCount( ifstream & );
// get number of student records in the file
int getRecordCount( fstream & );
// ask for a record number to search
int getRecordRequest( int );
// read a record in the file
Student readRecord( fstream &, int );
// print a row of field headings
void printRecordHeader();
// update a record at a (record numbered) location
bool updateRecord( fstream &, int );
// dalete a record at a (record numbered) location
bool deleteRecord( fstream &, int );
// check if a record is deleted
bool isDeletedRecord( Student );

#endif
