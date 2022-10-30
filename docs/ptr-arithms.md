# Pointer Arithmetics



1. [Pointer Expressions and Arithmetic](#Pointer-Expressions-and-Arithmetic)
2. [Converting Between Pointer Types](#Converting-Between-Pointer-Types-with-the-`reinterpret_cast`-Operator)
3. [Arrays and Pointers](#Arrays-and-Pointers)
4. [Companion Code](#Companion-Code)



## Pointer Expressions and Arithmetic

C++ enables pointer arithmetic—certain arithmetic operations may be performed on pointers. A pointer may be incremented (`++`) or decremented (`--`), an integer may be added to a pointer (`+` or `+=`), an integer may be subtracted from a pointer (`-` or `-=`) or one pointer may be subtracted from another of  the same type.

Assume that array `int v[5]` has been declared and that its first element is at memory location 3000. Assume that pointer  `vPtr` has been initialized to point to `v[0]` (i.e., the value of vPtr  is 3000). Variable `vPtr` can be initialized to point to array `v` with  either of the following statements

```cpp
int *vPtr = v;
int *vPtr = &v[ 0 ];
```



In conventional arithmetic, the addition `3000 + 2` yields the value  `3002`. This is normally not the case with pointer arithmetic. When an  integer is added to, or subtracted from, a pointer, the pointer is not  simply incremented or decremented by that integer, but by that integer  times the size of the object to which the pointer refers. For example,  the statement 

```cpp
vPtr += 2;
```

would produce  `3008` (`3000 + 2 * 4`), assuming that an `int` is stored in four bytes  of memory. When performing pointer arithmetic on a character array, the  results will be consistent with regular arithmetic, because each  character is one byte long. 

Pointer variables pointing to the  same array may be subtracted from one another. For example, if `vPtr`  contains the address 3000 and `v2Ptr` contains the address 3008, the  statement

```cpp
x = v2Ptr - vPtr;
```

would assign to `x` the number of array elements from `vPtr` to `v2Ptr`—in this case, 2. 

A pointer can be assigned to another pointer if both pointers are of the  same type. Otherwise, a cast operator (normally a reinterpret_cast;  discussed later in this section) must be used to convert the value of the  pointer on the right of the assignment to the pointer type on the left  of the assignment. The exception to this rule is the pointer to `void`  (i.e., `void *`), which is a generic pointer *capable of representing any  pointer type*. All pointer types can be assigned to a pointer of type  `void *` without casting. However, a pointer of type `void *` cannot be  assigned directly to a pointer of another type—the pointer of type `void *` must first be cast to the proper pointer type.

A `void *` pointer  *cannot be dereferenced*. For example, the compiler “knows” that a pointer to `int` refers to four bytes of memory on a machine with four-byte integers, but a pointer to `void` simply contains a memory address for an  unknown data type—the precise number of bytes to which the pointer refers and the type of the data are not known by the compiler. **The  compiler must know the data type to determine the number of bytes to be  dereferenced for a particular pointer**—for a pointer to `void`, this number of bytes cannot be determined from the type.

Pointers can be compared using equality and relational operators. **Comparisons using  relational operators are meaningless unless the pointers point to  members of the same array**. Pointer comparisons compare the addresses  stored in the pointers. A comparison of two pointers pointing to the  same array could show, for example, that one pointer points to a higher numbered element of the array than the other pointer does. A common use of pointer comparison is determining whether a pointer is 0 (i.e., the  pointer is a null pointer—it does not point to anything).

## Converting Between Pointer Types with the `reinterpret_cast` Operator

Unfortunately, most pointers that we use to copy/move data between memory locations or between secondary storage and main memory (e.g. arguments to functions memcopy, read, write etc.) as argument are not of type (`const char *` or `void *`) expected. To input/output or read/write objects of other types, we must convert the pointers to those objects to appropriate types; otherwise, the compiler will not compile these calls.

C++ provides the `reinterpret_cast` operator for cases like this in which a pointer of one type must be cast to an unrelated pointer type. Without a `reinterpret_cast` , the write statement that outputs the integer number will not compile because the compiler does not allow a pointer of type `int *` (the type returned by the expression `&number` ) to be passed to a function that expects an argument of type `const char *` —as far as the compiler is concerned, these types are incompatible. For example

```cpp
basic_ostream& write(
  const char_type* s,
  std::streamsize count
);
```

expects a pointer like `const char *` as the first argument. In order to write a data type other than a `char`, the `reinterpret_cast` operator is used like

```cpp
outFile.write(
  reinterpret_cast< const char * >( &number ),
  sizeof( number )
);
```

A reinterpret_cast is performed at compile time and does not change the value of the object to which its operand points. Instead, it requests that the compiler reinterpret the operand as the target type (specified in the angle brackets following the keyword `reinterpret_cast`)



## Arrays and Pointers

Arrays and pointers are intimately related in C++ and may be used almost  interchangeably. An array name can be thought of as a constant pointer.  Pointers can be used to do any operation involving array subscripting.

Assume the following declarations:

```cpp
int b[ 5 ]; // create 5-element int array b
int *bPtr; // create int pointer bPtr
```

Because the array name (without a subscript) is a (constant) pointer to the  first element of the array, we can set `bPtr` to the address of the first  element in array b with the statement

```cpp
bPtr = b; // assign address of array b to bPtr
```

This is equivalent to assigning the address of the first element of the array as follows:

```cpp
bPtr = &b[ 0 ]; // also assigns address of array b to bPtr
```

Array element `b[3]` can alternatively be referenced with the pointer expression

```cpp
*( bPtr + 3 )
```

The 3 in the preceding expression is the offset to the pointer. When the  pointer points to the beginning of an array, the offset indicates which  array element should be referenced, and the offset value is identical to the subscript. This notation is referred to as **pointer/ offset  notation**. The parentheses are necessary, because the precedence of `*` is higher than that of `+`. Without the parentheses, the preceding  expression would add 3 to a copy `*bPtr`’s value (i.e., 3 would be added to `b[0]`, assuming that `bPtr` points to the beginning of the array).  Just as the array element can be referenced with a pointer expression,  the address

```cpp
&b[ 3 ]
```

can be written with the pointer expression

```cpp
bPtr + 3
```

The array name (which is implicitly `const`) can be treated as a pointer and  used in pointer arithmetic. For example, the expression

```cpp
*( b + 3 )
```

also refers to the array element `b[3]`. In general, all subscripted array  expressions can be written with a pointer and an offset. In this case,  **pointer/offset notation** was used with the name of the array as a  pointer. The preceding expression does not modify the array name in any  way; b still points to the first element in the array.

Pointers can be subscripted exactly as arrays can. For example, the expression

```cpp
bPtr[ 1 ]
```

refers to the array element `b[1]`; this expression uses **pointer/subscript  notation**. Remember that an array name is a constant pointer; it always  points to the beginning of the array. Thus, the expression

```cpp
b += 3
```

causes a compilation error, because it attempts to modify the value of the array name (a constant) with pointer arithmetic.



## Companion Code

You can find these example programs in [doc_examples](../doc_examples/pointer_arithm).



[^ Top](#Pointer-Arithmetics)
