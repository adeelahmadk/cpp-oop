# Compiling Multiple-Source-File Programs



1. [Introduction](#Introduction)
2. [Storage Classes](#Storage-Classes)
    1. [Automatic Storage Class](#Automatic-Storage-Class)
    2. [Static Storage Class](#Static-Storage-Class)
3. [Companion Code](#Companion-Code)



## Introduction

There are several considerations when creating programs in multiple files. For example, the definition of a function must be entirely contained in one file, it cannot span two or more files. Issues with variable scope and visibility can be resolved by using appropriate storage-class. In this section we take a look at the considerations and time-tested techniques for the management of projects spanning multiple files.

This section explains some concepts that apply to all areas of C++, OOP or Non-OOP.

## Storage Classes

C++ provides five storage-class specifiers: **auto** , **register** , **extern** , **mutable** and **static**.

An identifier’s storage class determines the lifetime during which that identifier exists in memory. Some exist briefly, some are repeatedly created and destroyed and others exist for the entire execution of a program. 

An identifier’s *scope* is where the identifier can be referenced in a program. Some identifiers can be referenced throughout a program; others can be referenced from only limited portions of a program. Whereas, an identifier’s *linkage* determines whether it’s known only in the source file where it’s declared or across multiple files that are compiled, then linked together. An identifier’s storage-class specifier helps determine its scope and linkage.

The storage-class specifiers can be split into two storage classes: **automatic** storage class and **static** storage class. 



### Automatic Storage Class

Keywords `auto` and `register` are used to declare variables of the automatic storage class. Such variables are created when program execution enters the block in which they are defined, they exist while the block is active and they’re destroyed when the program exits the block.

#### Local Variables

Only local variables of a function can be of automatic storage class. A function’s local variables and parameters normally are of automatic storage class. For example

```cpp
auto double x;
```

The storage class specifier `auto` explicitly declares variables of automatic storage class.

#### Register Variables

The `register` keyword can be used only with local variables and function parameters. The compiler might ignore `register` declarations. For example, there might not be a sufficient number of CPU registers available for the compiler to use. The following definition suggests that the integer variable counter be placed in one of the computer’s registers

```cpp
register int counter = 1;
```

### Static Storage Class

Keywords `extern` and `static` declare identifiers for variables of the static storage class and for functions. Static storage-class variables exist from the point at which the program begins execution and last for the duration of the program.

There are two types of identifiers with static storage class—external identifiers (such as global variables and global function names) and local variables declared with the storage-class specifier `static`.

Local variables declared `static` are still known only in the function in which they’re declared, but, unlike automatic variables, static local variables retain their values when the function returns to its caller. The next time the function is called, the static local variables contain the values they had when the function last completed execution. All numeric variables of the static storage class are initialized to zero if they’re not explicitly initialized by you.

The following code snippet outlines the behavior of static storage-class

```cpp
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

```

The output is as follows

```
First call to each function:

Values on entering staticArrayInit:
array1[0] = 0  array1[1] = 0  array1[2] = 0
Values on exiting staticArrayInit:
array1[0] = 5  array1[1] = 5  array1[2] = 5

Values on entering automaticArrayInit:
array2[0] = 1  array2[1] = 2  array2[2] = 3
Values on exiting automaticArrayInit:
array2[0] = 6  array2[1] = 7  array2[2] = 8

Second call to each function:

Values on entering staticArrayInit:
array1[0] = 5  array1[1] = 5  array1[2] = 5
Values on exiting staticArrayInit:
array1[0] = 10  array1[1] = 10  array1[2] = 10

Values on entering automaticArrayInit:
array2[0] = 1  array2[1] = 2  array2[2] = 3
Values on exiting automaticArrayInit:
array2[0] = 6  array2[1] = 7  array2[2] = 8
```



#### What's Special about `static` and `extern`

Storage-class specifiers `extern` and `static` have special meaning when they’re applied explicitly to external identifiers such as global variables and global function names.

*Global variables are accessible to any function defined in the same file* after the variable is declared. Global variables also are *accessible to functions in other files*. However, *the global variables must be declared in each file in which they’re used*. For example, **to refer to global integer variable flag in another file**, you can use the declaration

```cpp
extern int flag;
```

This declaration uses the storage-class specifier `extern` to indicate that **variable flag is defined either later in the same file or in a different file**. The compiler informs the linker that unresolved references to variable flag appear in the file. If the linker finds a proper global definition, the linker resolves the references by indicating where flag is located. If the linker cannot locate a definition of flag , it issues an error message and does not produce an executable file. Any identifier that’s declared at file scope is `extern` by default.

It is possible to restrict the scope of a global variable or function to the file in which it is defined. The storage-class specifier `static`, when applied to a file scope variable or a function, prevents it from being used by any function that is not defined in the same file. This is referred to as **internal linkage**. The global variable declaration 

```cpp
 static double pi = 3.14159;
```

creates variable pi of type double, initializes it to 3.14159 and indicates that pi is known only to functions in the file in which it is defined. 

Global variables (except those that are `const`) and functions that are not preceded by `static` in their definitions have external linkage. This means they can be accessed in other files if those files contain proper declarations and/or function prototypes. 



## Companion Code

You can find these example programs in [doc_examples](../doc_examples/storage_classes).



[^ Top](#Compiling-Multiple-Source-File-Programs)
