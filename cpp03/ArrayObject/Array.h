/**
 * @file Array.h
 * @author Adeel Ahmad (6880680+adeelahmadk@users.noreply.github.com)
 * @brief Array class template definition with overloaded operators.
 * @version 0.1
 * @date 2022-08-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _ARRAY_H
#define _ARRAY_H

#include <iostream>
#include <iomanip>
#include <cstdlib> // exit function prototype
#include "../include/except.h"
using namespace std;

// Forward declarations for the class
template<typename T> class Array;
// Forward declaring global function templates
template<typename T> ostream &operator<<( ostream &output, const Array<T> &a );
template<typename T> istream &operator>>( istream &input, Array<T> &a );

/**
 * @brief Array template class definition
 *
 * @tparam T
 */
template<typename T>
class Array
{
    // global function prototypes
    friend ostream &operator<< <>( ostream &output, const Array<T> &a );
    friend istream &operator>> <>( istream &input, Array<T> &a );

    /*
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
    size_t size_; // number of memory blocks allocated to ptr_
    T *ptr_; // pointer to first element of pointer-based array
}; // end class Array

// default constructor for class Array (default size 10)
/**
 * @brief Construct a new Array< T>:: Array object
 *
 * @tparam T
 */
template<typename T>
Array<T>::Array()
{
    size_ = 10; // default arraySize
    initArray();
} // end Array default constructor

// constructor for class Array:
// creates an array of received size (default 10)
template<typename T>
Array<T>::Array( size_t arraySize )
{
    size_ = ( arraySize > 0 ? arraySize : 10 ); // validate arraySize
    initArray();
} // end Array default constructor

// copy constructor for class Array;
// must receive a reference to prevent infinite recursion
template<typename T>
Array<T>::Array( const Array<T> &arrayToCopy )
   : size_( arrayToCopy.size_ )
{
   ptr_ = new T[ size_ ]; // create space for pointer-based array

   for ( size_t i = 0; i < size_; i++ )
      ptr_[ i ] = arrayToCopy.ptr_[ i ]; // copy into object
} // end Array copy constructor

// destructor for class Array
template<typename T>
Array<T>::~Array()
{
   delete [] ptr_; // release pointer-based array space
} // end destructor

// class implementation to create & initialize dynamic array element
template<typename T>
void Array<T>::initArray()
{
   ptr_ = new T[ size_ ]; // create space for pointer-based array

   for ( size_t i = 0; i < size_; i++ )
      ptr_[ i ] = 0; // set pointer-based array element
}

// return number of elements of Array
template<typename T>
size_t Array<T>::getSize() const
{
   return size_; // number of elements in Array
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
      if ( size_ != right.size_ )
      {
         delete [] ptr_; // release space
         size_ = right.size_; // resize this object
         ptr_ = new T[ size_ ]; // create space for array copy
      } // end inner if

      for ( size_t i = 0; i < size_; i++ )
         ptr_[ i ] = right.ptr_[ i ]; // copy array into object
   } // end outer if

   return *this; // enables x = y = z, for example
} // end function operator=

// determine if two Arrays are equal and
// return true, otherwise return false
template<typename T>
bool Array<T>::operator==( const Array<T> &right ) const
{
   if ( size_ != right.size_ )
      return false; // arrays of different number of elements

   for ( size_t i = 0; i < size_; i++ )
      if ( ptr_[ i ] != right.ptr_[ i ] )
         return false; // Array contents are not equal

   return true; // Arrays are equal
} // end function operator==

// overloaded subscript operator for non-const Arrays;
// reference return creates a modifiable lvalue
template<typename T>
T &Array<T>::operator[]( size_t subscript )
{
   // check for subscript out-of-range error
   if ( subscript >= size_ )
   {
      cerr << "\nError: Subscript " << subscript
         << " out of range" << endl;
      // throw an exception object to the try-catch block
      // where exception occurred.
      throw IndexOutOfBoundException();
   } // end if

   return ptr_[ subscript ]; // reference return
} // end function operator[]

// overloaded subscript operator for const Arrays
// const reference return creates an rvalue
template<typename T>
T Array<T>::operator[]( size_t subscript ) const
{
   // check for subscript out-of-range error
   if ( subscript >= size_ )
   {
      cerr << "\nError: Subscript " << subscript
         << " out of range" << endl;
      // throw an exception object to the try-catch block
      // where exception occurred.
      throw IndexOutOfBoundException();
   } // end if

   return ptr_[ subscript ]; // returns copy of this element
} // end function operator[]

// overloaded input operator for class Array;
// inputs values for entire Array
template<typename T>
istream &operator>>( istream &input, Array<T> &a )
{
   for ( size_t i = 0; i < a.size_; i++ )
      input >> a.ptr_[ i ];

   return input; // enables cin >> x >> y;
} // end function

// overloaded output operator for class Array
template<typename T>
ostream &operator<<( ostream &output, const Array<T> &a )
{
   size_t i;

   // output private ptr-based array
   for ( i = 0; i < a.size_; i++ )
   {
      output << setw( 12 ) << a.ptr_[ i ];

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
