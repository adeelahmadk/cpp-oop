// Program to test class Time.
// NOTE: This file must be compiled with time.cxx.
#include <iostream>
#include "Time.h" // include definition of class Time from Time.h

using namespace std;

int main()
{
    Time t; // instantiate object t of class Time

    // output Time object t's initial values
    cout << "The initial universal time is ";
    t.printUniversal(); // 00:00:00

    cout << "\nThe initial standard time is ";
    t.printStandard(); // 12:00:00 AM
    t.setTime( 13, 27, 6 ); // change time

    // output Time object t's new values
    cout << "\n\nUniversal time after setTime is ";
    t.printUniversal(); // 13:27:06

    cout << "\nStandard time after setTime is ";
    t.printStandard(); // 1:27:06 PM

    t.setTime( 99, 99, 99 ); // attempt invalid settings

    // output t's values after specifying invalid values
    cout << "\n\nAfter attempting invalid settings:"
    << "\nUniversal time: ";
    t.printUniversal(); // 00:00:00

    cout << "\nStandard time: ";
    t.printStandard(); // 12:00:00 AM
    cout << endl;

    Time wakeUp( 6, 45, 0 ); // non-constant object
    const Time noon( 12, 0, 0 ); // constant object
                            // MEMBER       FUNCTION
    wakeUp.setHour( 18 );   // non-const    non-const

    noon.setHour( 12 );     // const        non-const

    wakeUp.getHour();       // non-const    const

    noon.getMinute();       // const        const
    noon.printUniversal();  // const        const

    noon.printStandard();   //const         non-const

/*  BAD PRACTICE!!
    cout << endl;

    // receiving ref to private member
    Time &tref = t.badSetHour(11);
    tref.hour = 35; // updating private member
*/

    cout << endl;

    // demo of cascaded function calls
    cout << "\nCalling setTime and printStandard in cascade: ";
    t.setTime(10, 48, 35).printStandard();
    cout << endl;

    return 0;
} // end main
