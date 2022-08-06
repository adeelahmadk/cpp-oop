// Declaration of class Time.
// Member functions are defined in Time.cpp

// To prevent multiple inclusions of header file
#ifndef TIME_H
#define TIME_H

// Time class definition
class Time
{
public:
    Time( int = 0, int = 0, int = 0 ); // default constructor

    // set functions, return Time & to enable cascaded calls
    Time & setTime( int, int, int ); // set hour, minute and second
    Time & setHour( int ); // set hour
    Time & setMinute( int ); // set minute
    Time & setSecond( int ); // set second

    // BAD PRACTICE!
    /* int &badSetHour( int ); // DANGEROUS reference return */

    // get functions (normally declared const)
    int getHour() const; // return hour
    int getMinute() const; // return minute
    int getSecond() const; // return second

    // print functions (normally declared const)
    void printUniversal() const; // print time in universal-time format
    void printStandard(); // print time in standard-time format
private:
    int hour; // 0 - 23 (24-hour clock format)
    int minute; // 0 - 59
    int second; // 0 - 59
}; // end class Time

#endif
