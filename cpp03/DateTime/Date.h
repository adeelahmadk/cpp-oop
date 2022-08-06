// Date class declaration.
// prevent multiple inclusions of header file
#ifndef DATE_H
#define DATE_H

#include <iostream>

using namespace std;

// class Date definition
class Date
{
    friend ostream &operator<<( ostream &, const Date & );

public:
    Date( int = 1, int = 1, int = 2000 ); // default constructor
    void setDate( int, int, int ); // set month, day, year
    Date &operator++(); // prefix increment operator
    Date operator++( int ); // postfix increment operator
    const Date &operator+=( int ); // add days, modify object
    bool endOfMonth( int ) const; // is date at the end of month?
    /* static members */
    static bool leapYear( int ); // is date in a leap year?

private:
    int month;
    int day;
    int year;
    static const int days[]; // array of days per month

    void helpIncrement();
}; // end class Date

#endif
