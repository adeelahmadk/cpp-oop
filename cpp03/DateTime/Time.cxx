// Member-function definitions for class Time.
#include <iostream>
#include <iomanip>
#include "Time.h" // include definition of class Time from time.h

using namespace std;

// Time constructor initializes each data member to zero.
// Ensures all Time objects start in a consistent state.
Time::Time( int h, int m, int s )
{
    setTime(h, m, s);
} // end Time constructor

// set new Time value using universal time; ensure that
// the data remains consistent by setting invalid values to zero
Time & Time::setTime( int hour, int minute, int second )
{
    setHour(hour);
    setMinute(minute);
    setSecond(second);
    return *this;
} // end function setTime

// set hour
Time & Time::setHour( int h )
{
    hour = ( h >= 0 && h < 24 ) ? h : 0; // validate hour
    return *this;
}

// set minute
Time & Time::setMinute( int m )
{
    minute = ( m >= 0 && m < 60 ) ? m : 0; // validate minute
    return *this;
}

// set second
Time & Time::setSecond( int s )
{
    second = ( s >= 0 && s < 60 ) ? s : 0; // validate second
    return *this;
}

// Example of what NOT TO DO: BAD PRACTICE!!
/* int & Time::badSetHour( int h )
{
    hour = ( h >= 0 && h < 24 ) ? h : 0; // validate hour
    return hour; // DANGEROUS reference return
    // returning a reference to a private data member
    // will make it possible to update it from outside
} */

// return hour
int Time::getHour() const
{
    return hour;
}

// return minute
int Time::getMinute() const
{
    return minute;
}

// return second
int Time::getSecond() const
{
    return second;
}

// print Time in universal-time format (HH:MM:SS)
void Time::printUniversal() const
{
    cout << setfill( '0' ) << setw( 2 ) << hour << ":"
        << setw( 2 ) << minute << ":" << setw( 2 ) << second ;
} // end function printUniversal

// print Time in standard-time format (HH:MM:SS AM or PM)
void Time::printStandard()
{
    cout << ( ( hour == 0 || hour == 12 ) ? 12 : hour % 12 ) << ":"
        << setfill( '0' ) << setw( 2 ) << minute << ":" << setw( 2 )
        << second << ( hour < 12 ? " AM" : " PM" );
} // end function printStandard
