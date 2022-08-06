// Using template functions.
#include <iostream>
#include <iomanip>
using namespace std;

// function template printArray definition
template< typename ArrayType >
void printArray(
        const ArrayType * const arr,  // a const pointer to const template type array
        size_t count  // size of the array
    )
{
    for ( size_t i = 0; i < count; i++ )
    {
        // print elements in 5 columns
        if( i % 5 == 0 )
            cout << endl;
        // ostream operator should know how to print 'ArrayType' data.
        cout << setw(10) << arr[i];
    }

    cout << endl;
} // end function template printArray

int main()
{
   const int aCount = 5; // size of array a
   const int bCount = 7; // size of array b
   const int cCount = 6; // size of array c

   int a[ aCount ] = { 1, 2, 3, 4, 5 };
   double b[ bCount ] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7 };
   char c[ cCount ] = "HELLO"; // 6th position for null

   cout << "Array a contains:" << endl;

   // call integer function-template specialization
   printArray( a, aCount );

   cout << "Array b contains:" << endl;

   // call double function-template specialization
   printArray( b, bCount );

   cout << "Array c contains:" << endl;

   // call character function-template specialization
   printArray( c, cCount );
} // end main
