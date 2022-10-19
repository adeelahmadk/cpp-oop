/**
 * utils.cxx:    An assorted collection of
 *               utility function definitions
 */
#include <iostream>
#include <iomanip>
#include "utils.h"
using namespace std;

/**
 * Function: rangedRand
 *
 * generate unbiased uniform random numbers
 * in the range [min, max].
 *
 * r:  a range object carrying min & max values
 *
 * returns: random int value in the range
 */
int rangedRand( const range &r )
{
    unsigned int delta = (r.max - r.min + 1);
    int divisor = ((RAND_MAX / delta) + 1);
    int random_value;
    /* while(random_value > max) */
    random_value = r.min + rand() / divisor;
    return random_value;
} // end function rangedRand

/**
 * Function: printArray
 *
 * prints an array in columner format
 *
 * arr:   array to be printed
 * count: size of the array to print
 *
 * returns: nothing
 */
void printArray( const int * const arr, size_t count )
{
    for ( size_t i = 0; i < count; i++ )
    {
        if( i > 0 && i % 5 == 0 )
            cout << endl;
        cout << setw(10) << arr[ i ] << " ";
    }
    cout << endl;
} // end function template printArray
