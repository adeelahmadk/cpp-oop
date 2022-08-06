/**
  * sorting.h: A collection of sorting algorithm
  *            prototype declarations.
  */
#ifndef _SORTING_H
#define _SORTING_H

#include <cstddef>

// perform comparison for ascending sort
bool ascending( int, int );

// perform comparison for descending sort
bool descending( int, int );

// namespace to avoid confusion with std::swap
namespace sorting {
    // swap two values in referenced locations
    void swap( int &, int & );
}

// sort an array
void selectionSort(
            int [],  // unsorted int array
            size_t,  // size of the array
            bool (*)( int, int ) // pointer to the comparison function
        );

#endif /* _SORTING_H */
