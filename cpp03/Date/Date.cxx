// Date class member-function definitions.
#include <iostream>
#include "Date.h" // include definition of class Date from Date.h

using namespace std;

// initialize static member; one classwide copy
const int Date::days[] =
   { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// Date constructor (should do range checking)
Date::Date( int m, int d, int y )
{
    setDate(m, d, y);
} // end Date constructor

// set month, day, year
void Date::setDate( int mm, int dd, int yy )
{
    month = ( mm >= 1 && mm <= 12 ) ? mm : 1;
    year = ( yy >= 1900 && yy <= 2100 ) ? yy : 1900;

    // test for a leap year
    if ( month == 2 && leapYear( year ) )
        day = ( dd >= 1 && dd <= 29 ) ? dd : 1;
    else
        day = ( dd >= 1 && dd <= days[ month ] ) ? dd : 1;
} // end function setDate

// prefix increment operator
Date &Date::operator++()
{
    helpIncrement(); // first increment date
    return *this; // then retrun reference to create lvalue
} // end function operator++

// postfix increment operator. note the
// "dummy int parameter" doesn't have a
// parameter name.
Date Date::operator++( int )
{
    Date temp = *this; // hold current state of object
    helpIncrement(); // increment date
    // return unincremented save temporary object
    return temp; // value return, not a reference return
} // end function operator++

// add specified number of days to date
const Date &Date::operator+=( int addDays )
{
    for( int i = 0; i < addDays; i++ )
        helpIncrement();

    return *this; // enable cascading
} // end function operator+=

// check if the year is a leap year?
bool Date::leapYear( int testYear )
{
    if( ( testYear % 400 == 0 ) ||
        ( testYear % 100 != 0 && testYear % 4 == 0 ) )
        return true; // a leap year

    return false; // not a leap year
} // end function leapYear

// is date at the end of month?
bool Date::endOfMonth( int testDay ) const
{
    if( month == 2 && leapYear( year ) )
        return ( testDay == 29 ); // last day of feb in leap year
    else
        return ( testDay == days[ month ] );
} // end function endOfMonth

// function to help increment the date
void Date::helpIncrement()
{
    // day is not end of month
    if( !endOfMonth( day ) )
    {
        day++; // increment day
    }
    else
    {
        if( month < 12 ) // day is end of month but not year
        {
            month++; // increment month
            day = 1; // 1st day of new month
        }
        else // last day of the year
        {
            year++; // increment year
            month = 1; // 1st month of new year
            day = 1; // 1st day of new month
        }
    }
} // end function helpIncrement

// overloaded stream insertion operator (<<)
ostream &operator<<( ostream &out, const Date &date )
{
    static string monthName[ 13 ] = {
        "", "January", "February", "March",
        "April", "May", "June", "July", "August",
      "September", "October", "November", "December" };
    out << monthName[ date.month ]
        << " "
        << date.day
        << ", "
        << date.year;
    return out;
} // end function operator<<
/* Whether an operator function is implemented as a member
 * function or as a global function, the operator is still
 * used the same way in expressions. So which is best?
 * When an operator function is implemented as a member
 * function, the leftmost (or only) operand must be an object
 * (or a reference to an object) of the operator’s class. If
 * the left operand must be an object of a different class or
 * a fundamental type, this operator function must be
 * implemented as a global function.
 * A global operator function can be made a friend of a class
 * if that function must access private or protected members
 * of that class directly.
 * */
