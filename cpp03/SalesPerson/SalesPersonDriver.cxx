// Utility function demonstration.
// Compile this program with SalesPerson.cpp
// include SalesPerson class definition from SalesPerson.h
#include <iostream>
#include "SalesPerson.h"

using namespace std;

int main()
{
    // public static data members can be accessed and can
    // also be updated (if not declared const) from outside
    // the class scope **without creating an object**
    cout << "Max.length for first & last names is "
        << SalesPerson::nameLength << "\n" << endl;

    SalesPerson s; // create SalesPerson object s

    s.getSalesFromUser(); // note simple sequential code; there are
    s.printAnnualSales(); // no control statements in main

    return 0;
} // end main
