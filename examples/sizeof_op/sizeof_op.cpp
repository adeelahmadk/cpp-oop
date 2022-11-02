// Sizeof operator when used on an array name
// returns the number of bytes in the array.
#include <iostream>
using namespace std;
size_t getSize( double * ); // prototype

int main()
{
    double array[ 20 ]; // 20 doubles; occupies 160 bytes on our system
    cout << "The number of bytes in the array is " << sizeof( array );
    cout << "\nThe number of bytes returned by getSize is "
        << getSize( array )<< endl;
    cout << "Nmber elements in the array are "
        << sizeof(array) / sizeof(array[0]) << endl;
} // end main

// return size of ptr
size_t getSize( double *ptr )
{
    return sizeof( ptr );
} // end function getSize
