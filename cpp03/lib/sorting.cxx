/**
  * A collection of sorting algorithm
  * function definitions
  */
#include <iostream>
#include "sorting.h"
using namespace std;

/**
  * Function: swap
  *
  * Swaps value of two reference parameters.
  *
  * x: a reference to int
  * y: a reference to int
  *
  * returns: nothing
  */
void sorting::swap(int &x, int &y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

/**
  * Function: ascending
  *
  * Compares value of two parameters
  * for ascending order sorting.
  *
  * x: int variable
  * y: int variable
  *
  * returns: boolean result of the comparison
  */
bool ascending( int x, int y )
{
    return x > y;
}

/**
  * Function: descending
  *
  * Compares value of two parameters
  * for descending order sorting.
  *
  * x: int variable
  * y: int variable
  *
  * returns: boolean result of the comparison
  */
bool descending( int x, int y )
{
    return x < y;
}

/**
  * Function: selectionSort
  *
  * Performs Selection Sort algorithm
  * on int array.
  *
  * A:           an array of integers
  * legth:       length of array
  * compareFcn:  pointer to the comparison function
  *
  * returns: nothing
  */
void selectionSort(
            int A[],  // array to sort
            size_t length,  // length of the array
            bool (*compareFcn)( int, int ) // pointer to the comparison function
        )
{
    // Step through each element of the array
    for( size_t startIndex = 0; startIndex < length - 1; startIndex++ )
    {
        // index of the smallest/greatest element so far
        size_t swapIndex = startIndex;
        // Look for smallest/greatest element remaining in the array
        for( size_t currentIndex = startIndex + 1;
                currentIndex < length;
                currentIndex++ )
        {
            // If the current element is smaller/greater than
            // our previously found smallest/greatest
            if( compareFcn( A[swapIndex], A[currentIndex] ) ) // use comparison function
            {
                // inthis is the new smallest/greatest number
                // for this iteration
                swapIndex = currentIndex;
            }
        }
        // Swap our start element with our smallest/greatest element
        sorting::swap( A[startIndex], A[swapIndex] );
    }
}


