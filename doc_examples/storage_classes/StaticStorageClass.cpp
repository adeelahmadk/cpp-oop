// Storage Classes
// Static arrays are initialized to zero.
#include <iostream>
using namespace std;

void staticArrayInit( void ); // function prototype
void automaticArrayInit( void ); // function prototype
const int arraySize = 3; 

int main()
{
   cout << "First call to each function:\n";
   staticArrayInit();
   automaticArrayInit();

   cout << "\n\nSecond call to each function:\n";
   staticArrayInit();
   automaticArrayInit();
   cout << endl;
} // end main

// function to demonstrate a static local array
void staticArrayInit( void )
{
   // initializes elements to 0 first time function is called
   static int array1[ arraySize ]; // static local array 

   cout << "\nValues on entering staticArrayInit:\n";

   // output contents of array1
   for ( int i = 0; i < arraySize; i++ )
      cout << "array1[" << i << "] = " << array1[ i ] << "  ";

   cout << "\nValues on exiting staticArrayInit:\n";

   // modify and output contents of array1
   for ( int j = 0; j < arraySize; j++ )
      cout << "array1[" << j << "] = " << ( array1[ j ] += 5 ) << "  ";
} // end function staticArrayInit

// function to demonstrate an automatic local array
void automaticArrayInit( void )
{
   // initializes elements each time function is called
   int array2[ arraySize ] = { 1, 2, 3 }; // automatic local array

   cout << "\n\nValues on entering automaticArrayInit:\n";

   // output contents of array2
   for ( int i = 0; i < arraySize; i++ )
      cout << "array2[" << i << "] = " << array2[ i ] << "  ";

   cout << "\nValues on exiting automaticArrayInit:\n";

   // modify and output contents of array2
   for ( int j = 0; j < arraySize; j++ )
      cout << "array2[" << j << "] = " << ( array2[ j ] += 5 ) << "  ";
} // end function automaticArrayInit

