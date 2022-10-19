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
) {
    // Step through each element of the array
    for( size_t startIndex = 0; startIndex < length - 1; startIndex++ ) {
        // index of the smallest/greatest element so far
        size_t swapIndex = startIndex;
        // Look for smallest/greatest element remaining in the array
        for( 
            size_t currentIndex = startIndex + 1;
            currentIndex < length;
            currentIndex++
        ) {
            // If the current element is smaller/greater than
            // our previously found smallest/greatest
            if( compareFcn( A[swapIndex], A[currentIndex] ) ) {
                // inthis is the new smallest/greatest number
                // for this iteration
                swapIndex = currentIndex;
            }
        }
        // Swap our start element with our smallest/greatest element
        sorting::swap( A[startIndex], A[swapIndex] );
    }
}


void insertionSort(
        int A[],
        size_t length,
        bool (*compareFcn)( int, int )
) {
    int insert;
    for ( size_t next = 1; next < length; next++ ) {
        insert = A[ next ]; // store the value in the current element
        size_t moveItem = next; // initialize location to place element
        // search for the location in which to put the current element
        while ( ( moveItem > 0 ) && compareFcn( A[moveItem - 1], insert ) ) {
            // shift element one slot to the right
            A[ moveItem ] = A[ moveItem - 1 ];
            moveItem--;
        } // end while
        A[ moveItem ] = insert; // place inserted element into the array
    } // end for
}
