/**
 * driver program to test sorting library
 */
#include <iostream>
#include <ctime>
#include "utils.h"
#include "sorting.h"

using namespace std;

/**
 * Function: initRandArray
 *
 * initialize an int array with unbiased uniform
 * random numbers in the range [min, max].
 *
 * min:  minimum value in the range
 * max:  maximum value in the range
 *
 * returns: nothing
 */
void initRandArray( int arr[], size_t size, const range r )
{
    for( size_t i = 0; i < size; i++)
        arr[i] = rangedRand( r );
}

int main()
{
    const size_t N = 20;
    int arr[ N ] = { 0 };

    // initialize random number generator
    srand(time(NULL));

    // randomly initialize the array in range [1, 100]
    initRandArray( arr, N, range(1, 100) );
    cout << "Array after random initialization:" << endl;
    printArray(arr, N);

    // sort the array in ascending order
    selectionSort(
            arr,  // array to be sorted
            N,  // size of the array
            ascending  // pointer to the comparison function
        );

    cout << "Array after ascending sort:" << endl;
    printArray(arr, N);

    cout << "\nAgain randomly initialize the array:\n" << endl;

    // randomly initialize the array in range [-100, 100]
    initRandArray( arr, N, range(-100, 100) );
    cout << "Array after random initialization:" << endl;
    printArray(arr, N);

    // sort the array in descending order
    selectionSort(
            arr,  // array to be sorted
            N,  // size of the array
            descending  // pointer to the comparison function

        );

    cout << "Array after descending sort:" << endl;
    printArray(arr, N);

    return 0;
}

