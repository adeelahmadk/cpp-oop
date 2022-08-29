// Array class driver program.
#include <iostream>
#include "Array.h"
using namespace std;

int main()
{
    Array< int > integers1( 7 ); // seven-element Array
    Array< int > integers2; // 10-element Array by default

    // print integers1 size and contents
    cout << "Size of Array integers1 is "
      << integers1.getSize()
      << "\nArray after initialization:\n" << integers1;

    // print integers2 size and contents
    cout << "\nSize of Array integers2 is "
      << integers2.getSize()
      << "\nArray after initialization:\n" << integers2;

    // input and print integers1 and integers2
    cout << "\nEnter 17 integers:" << endl;
    cin >> integers1 >> integers2;

    cout << "\nAfter input, the Arrays contain:\n"
      << "integers1:\n" << integers1
      << "integers2:\n" << integers2;

    /* try-catch blocks provide mechanism to handle logical errors
     * that my crash our program if not handled properly.
     */
    // try block encloses the code where an exception may occur
    try
    {
        cout << "\nAttempt to access an out-of-bound index\n"
            << "integers1[9]: " << integers1[9] << endl;
    }
    // here we catch the possible exception
    // objects thrown by called functions
    catch(IndexOutOfBoundException &exception)
    {
        cout << "Exception occurred: "
            << exception.what() << endl;
    }

    // use overloaded inequality (!=) operator
    cout << "\nEvaluating: integers1 != integers2" << endl;

    if ( integers1 != integers2 )
      cout << "integers1 and integers2 are not equal" << endl;

    // create Array integers3 using integers1 as an
    // initializer; print size and contents
    Array< int > integers3( integers1 ); // invokes copy constructor

    cout << "\nSize of Array integers3 is "
      << integers3.getSize()
      << "\nArray after initialization:\n" << integers3;

    // use overloaded assignment (=) operator
    cout << "\nAssigning integers2 to integers1:" << endl;
    integers1 = integers2; // note target Array is smaller

    cout << "integers1:\n" << integers1
      << "integers2:\n" << integers2;

    // use overloaded equality (==) operator
    cout << "\nEvaluating: integers1 == integers2" << endl;

    if ( integers1 == integers2 )
      cout << "integers1 and integers2 are equal" << endl;

    // use overloaded subscript operator to create rvalue
    cout << "\nintegers1[5] is " << integers1[ 5 ];

    // use overloaded subscript operator to create lvalue
    cout << "\n\nAssigning 1000 to integers1[5]" << endl;
    integers1[ 5 ] = 1000;
    cout << "integers1:\n" << integers1;

    // try block where an IndexOutOfBoundException may occur
    try
    {
        // attempt to use out-of-range subscript
        cout << "\nAttempt to assign 1000 to integers1[15]" << endl;
        integers1[ 15 ] = 1000; // ERROR: out of range
    }
    // here we catch the possible exception
    // objects thrown by called functions
    catch(IndexOutOfBoundException &exception)
    {
        cout << "Exception occurred: "
            << exception.what() << endl;
    }

    IntegerArray integers4( 5 );
    for( size_t i = 0; i < integers4.getSize(); i++ )
        integers4[i] = 2*i + 1;

    cout << "\nintegers4:\n" << integers4;
    if(integers4[2] < integers4[3])
        cout << "\nsubscript operator is overloaded." << endl;

    return 0;
} // end main
