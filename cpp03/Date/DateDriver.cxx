// Demonstrating that class objects can be assigned
// to each other using default memberwise assignment.
#include <iostream>
#include "Date.h" // include definition of class Date from Date.h

using namespace std;

string bool2String(bool value)
{
    return (value? "True" : "False");
}

int main()
{
    Date date1( 7, 4, 2004 );
    Date date2; // date2 defaults to 1/1/2000
    cout << "date1 = "
        << date1;
    cout << "\ndate2 = "
        << date2;
    date2 = date1; // default memberwise assignment
    cout << "\n\nAfter default memberwise assignment, date2 = "
        << date2 << endl;
    cout << "Incremented date2: " << ++date2 << endl;
    date2 += 35;
    cout << "date2 after 35 days: " << date2 << endl;
    cout << "\nIs 2022 a leap year? : "
        << bool2String( Date::leapYear( 2022 ) )
        << endl;
} // end main
