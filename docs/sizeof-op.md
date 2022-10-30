# Data Types and Memory Allocation



1. [`sizeof` operator](#`sizeof`-operator)
2. [Companion Code](#Companion-Code)



## `sizeof` operator

The unary operator `sizeof` determines the size of an array (or of any other data type, variable or constant) in bytes during program compilation. When applied to the name of an array, as in code snippet below, the `sizeof` operator returns the total number of bytes in the array as a value of type `size_t`. The computer we used to compile this program stores variables of type `double` in 8 bytes of memory, and array is declared to have 20 elements (line 10), so array uses 160 bytes in memory. When applied to a pointer parameter (line 20) in a function that receives an array as an argument, the `sizeof` operator returns the size of the pointer in bytes (4 on the system we used)—not the size of the array.

```cpp
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
    		<< getSize( array ) << endl;
    cout << "Nmber elements in the array are "
        << sizeof(array) / sizeof(array[0]) << endl;
} // end main

// return size of ptr
size_t getSize( double *ptr )
{
		return sizeof( ptr );
} // end function getSize
```

The number of elements in an array also can be determined using the results of two
`sizeof` operations. For example, consider the following array declaration:

```cpp
double realArray[ 22 ];
```

If variables of data type `double` are stored in eight bytes of memory, array `realArray` contains a total of 176 bytes. To determine the number of elements in the array, the following expression (which is evaluated at compile time) can be used:

```cpp
sizeof realArray / sizeof( realArray[ 0 ] )
```

The expression determines the number of bytes in array `realArray` (176) and divides that value by the number of bytes used in memory to store the array’s first element (typically 8 for a `double` value)—the result is the number of elements in `realArray` (22).

The following code snippet uses `sizeof` to calculate the number of bytes used to store most of the standard data types. The output shows that the types double and long double have the same size. Types may have different sizes based on the platform running the program.

```cpp
// Demonstrating the sizeof operator.
#include <iostream>
using namespace std;

int main()
{
    char c; // variable of type char
    short s; // variable of type short
    int i; // variable of type int
    long l; // variable of type long
    float f; // variable of type float
    double d; // variable of type double
    long double ld; // variable of type long double
    int array[ 20 ]; // array of int
    int *ptr = array; // variable of type int *
    cout << "sizeof c = " << sizeof c
        << "\tsizeof(char) = " << sizeof( char )
        << "\nsizeof s = " << sizeof s
        << "\tsizeof(short) = " << sizeof( short )
        << "\nsizeof i = " << sizeof i
        << "\tsizeof(int) = " << sizeof( int )
        << "\nsizeof l = " << sizeof l
        << "\tsizeof(long) = " << sizeof( long )
        << "\nsizeof f = " << sizeof f
        << "\tsizeof(float) = " << sizeof( float )
        << "\nsizeof d = " << sizeof d
        << "\tsizeof(double) = " << sizeof( double )
        << "\nsizeof ld = " << sizeof ld
        << "\tsizeof(long double) = " << sizeof( long double )
        << "\nsizeof array = " << sizeof array
        << "\nsizeof ptr = " << sizeof ptr << endl;
} // end main
```

Output

```
sizeof c = 1	sizeof(char) = 1
sizeof s = 2	sizeof(short) = 2
sizeof i = 4	sizeof(int) = 4
sizeof l = 8	sizeof(long) = 8
sizeof f = 4	sizeof(float) = 4
sizeof d = 8	sizeof(double) = 8
sizeof ld = 16	sizeof(long double) = 16
sizeof array = 80
sizeof ptr = 8
```

The number of bytes used to store a particular data type may vary among systems. When writing programs that depend on data type sizes, and that will run on several computer systems, use `sizeof` to determine the number of bytes used to store the data types.



## Companion Code

You can find these example programs in [doc_examples](../doc_examples/sizeof_op).



[^ Top](#Data-Types-and-Memory-Allocation)