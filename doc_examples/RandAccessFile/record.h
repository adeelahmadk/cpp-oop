// record.h
#ifndef RECORD_H
#define RECORD_H

#include <fstream>
#include <string>
using namespace std;

// const length for name char array
const int NAME_LENGTH = 30;

// alias definition for a student record
typedef struct {
    int id;
    char name[NAME_LENGTH];
    float score;
} student;

// get number of student records in the file
int getRecordCount( ifstream & );
// get number of student records in the file
int getRecordCount( fstream & );
// ask for a record number to search
int getRecordRequest( int );
// read a record in the file
student readRecord( fstream &, int );
// print a row of field headings
void printRecordHeader();
// print a record
void printRecord( student );
// update a record at a (record numbered) location
bool updateRecord( fstream &, int );
// dalete a record at a (record numbered) location
bool deleteRecord( fstream &, int );
// check if a record is deleted
bool isDeletedRecord( student );

#endif
