/**
* utils.h:  Prototypes declarations of an assorted
*           collection of utility functions
*/
#ifndef _UTILS_H
#define _UTILS_H
#include <climits>
#include <cstdlib>
using namespace std;

// a range object for rangedRand
struct _range {
    _range( int mi, int ma ): min(mi), max(ma) {}
    int min;
    int max;
};
typedef _range range;

// generate uniform random numbers in the range [min, max].
int rangedRand( const range );
// prints an array in columner format.
void printArray( const int * const, size_t );

#endif /* _UTILS_H */
