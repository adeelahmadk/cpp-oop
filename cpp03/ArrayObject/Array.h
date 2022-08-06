// Array.h
// Array class template definition with overloaded operators.
#ifndef _ARRAY_H
#define _ARRAY_H

#include <iostream>
#include <iomanip>
#include <cstdlib> // exit function prototype
#include "except.h"
using namespace std;

// Forward declarations for the class
template<typename T> class Array;
// Forward declaring global function templates
template<typename T> ostream &operator<<( ostream &output, const Array<T> &a );
template<typename T> istream &operator>>( istream &input, Array<T> &a );

// template class declaration
template<typename T>
class Array
{
    // global function prototypes
    friend ostream &operator<< <>( ostream &output, const Array<T> &a );
    friend istream &operator>> <>( istream &input, Array<T> &a );

    /**
     *
     * Methods alternate to the Forward Declarations.
     * - define the friend function within the class body at the
     *   same moment you declare it to be a `friend`.
     * - declare (global) friend function prototypes with a
     *   different template parameter (other than T).
     */

public:
    // as type deduction doesn't work for default argument
    // in case of template classes
    Array(); // default constructor
    Array( size_t ); // constructor
    Array( const Array<T> & ); // copy constructor
    ~Array(); // destructor
    size_t getSize() const; // return size

    const Array &operator=( const Array<T> & ); // assignment operator
    bool operator==( const Array<T> & ) const; // equality operator

    // inequality operator; returns opposite of == operator
    bool operator!=( const Array<T> &right ) const
    {
        return ! ( *this == right ); // invokes Array::operator==
    } // end function operator!=

    // subscript operator for non-const objects returns modifiable lvalue
    T &operator[]( size_t );

    // subscript operator for const objects returns rvalue
    T operator[]( size_t ) const;
private:
    void initArray();
    size_t size; // pointer-based array size
    T *ptr; // pointer to first element of pointer-based array
}; // end class Array

// default constructor for class Array (default size 10)
template<typename T>
Array<T>::Array()
{
    size = 10; //( arraySize > 0 ? arraySize : 10 ); // validate arraySize
    initArray();
} // end Array default constructor

// constructor for class Array:
// creates an array of received size (default 10)
template<typename T>
Array<T>::Array( size_t arraySize )
{
    size = ( arraySize > 0 ? arraySize : 10 ); // validate arraySize
    initArray();
} // end Array default constructor

// copy constructor for class Array;
// must receive a reference to prevent infinite recursion
template<typename T>
Array<T>::Array( const Array<T> &arrayToCopy )
   : size( arrayToCopy.size )
{
   ptr = new T[ size ]; // create space for pointer-based array

   for ( size_t i = 0; i < size; i++ )
      ptr[ i ] = arrayToCopy.ptr[ i ]; // copy into object
} // end Array copy constructor

// destructor for class Array
template<typename T>
Array<T>::~Array()
{
   delete [] ptr; // release pointer-based array space
} // end destructor

// class implementation to create & initialize dynamic array element
template<typename T>
void Array<T>::initArray()
{
   ptr = new T[ size ]; // create space for pointer-based array

   for ( size_t i = 0; i < size; i++ )
      ptr[ i ] = 0; // set pointer-based array element
}

// return number of elements of Array
template<typename T>
size_t Array<T>::getSize() const
{
   return size; // number of elements in Array
} // end function getSize

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template<typename T>
const Array<T> &Array<T>::operator=( const Array<T> &right )
{
   if ( &right != this ) // avoid self-assignment
   {
      // for Arrays of different sizes, deallocate original
      // left-side array, then allocate new left-side array
      if ( size != right.size )
      {
         delete [] ptr; // release space
         size = right.size; // resize this object
         ptr = new T[ size ]; // create space for array copy
      } // end inner if

      for ( size_t i = 0; i < size; i++ )
         ptr[ i ] = right.ptr[ i ]; // copy array into object
   } // end outer if

   return *this; // enables x = y = z, for example
} // end function operator=

// determine if two Arrays are equal and
// return true, otherwise return false
template<typename T>
bool Array<T>::operator==( const Array<T> &right ) const
{
   if ( size != right.size )
      return false; // arrays of different number of elements

   for ( size_t i = 0; i < size; i++ )
      if ( ptr[ i ] != right.ptr[ i ] )
         return false; // Array contents are not equal

   return true; // Arrays are equal
} // end function operator==

// overloaded subscript operator for non-const Arrays;
// reference return creates a modifiable lvalue
template<typename T>
T &Array<T>::operator[]( size_t subscript )
{
   // check for subscript out-of-range error
   if ( subscript < 0 || subscript >= size )
   {
      cerr << "\nError: Subscript " << subscript
         << " out of range" << endl;
      // throw an exception object to the try-catch block
      // where exception occurred.
      throw IndexOutOfBoundException();
   } // end if

   return ptr[ subscript ]; // reference return
} // end function operator[]

// overloaded subscript operator for const Arrays
// const reference return creates an rvalue
template<typename T>
T Array<T>::operator[]( size_t subscript ) const
{
   // check for subscript out-of-range error
   if ( subscript < 0 || subscript >= size )
   {
      cerr << "\nError: Subscript " << subscript
         << " out of range" << endl;
      // throw an exception object to the try-catch block
      // where exception occurred.
      throw IndexOutOfBoundException();
   } // end if

   return ptr[ subscript ]; // returns copy of this element
} // end function operator[]

// overloaded input operator for class Array;
// inputs values for entire Array
template<typename A>
istream &operator>>( istream &input, Array<A> &a )
{
   for ( size_t i = 0; i < a.size; i++ )
      input >> a.ptr[ i ];

   return input; // enables cin >> x >> y;
} // end function

// overloaded output operator for class Array
template<typename A>
ostream &operator<<( ostream &output, const Array<A> &a )
{
   size_t i;

   // output private ptr-based array
   for ( i = 0; i < a.size; i++ )
   {
      output << setw( 12 ) << a.ptr[ i ];

      if ( ( i + 1 ) % 4 == 0 ) // 4 numbers per row of output
         output << endl;
   } // end for

   if ( i % 4 != 0 ) // end last line of output
      output << endl;

   return output; // enables cout << x << y;
} // end function operator<<

// commonly used class template specializations
typedef Array< int > IntegerArray;
typedef Array< float > FloatArray;
typedef Array< double > DoubleArray;

#endif /* _ARRAY_H */
