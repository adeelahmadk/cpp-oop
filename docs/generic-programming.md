# Generic Programming



[Introduction](#Introduction)

1. [Function Templates](#Function-Templates)
2. [Class Templates](#Class-Templates)
3. [Class Template Specializations](#Class-Template-Specializations)
4. [Nontype Parameters and Default Types](#Nontype-Parameters-and-Default-Types)
5. [Class Template Specializations Summarized](#Class-Template-Specializations-Summarized)
6. [Limitations of Templates prior to C++11](#Limitations-of-Templates-prior-to-C++11)



## Introduction

C++ requires us to declare variables, functions, and most other kinds of entities using specific types. However, a lot of code looks the same for different types. For example, the implementation of the algorithm *quick sort* looks structurally the same for different data structures, such as arrays of `int`s or `vector`s of `string`s, as long as the contained types can be compared to each other.

If a programming language doesn’t support a special language feature for this kind of **genericity**, you only have bad alternatives:

1. You can implement the same behavior again and again for each type that needs this behavior.
2. You can write general code for a common base type such as `Object` or `void*`.
3. You can use special preprocessors.

Most modern programming languages provide features to implement this paradigm called **Generic Programming**. It is a style of programming in which algorithms are written in terms of types *to-be-specified-later* that are then instantiated when needed for specific types provided as parameters. In C++ it's implemented through **Templates** which bring in some powerful *software reuse* features. **Function templates** and **class templates** enable us to specify, with a single code segment, an entire range of related (overloaded) functions—called **function-template specializations**—or an entire range of related classes—called **class-template specializations**. This technique is called **generic programming**.

### Function Templates

Overloaded functions normally perform similar or identical operations on different types of data. If the operations are identical for each type, they can be expressed more compactly and conveniently using function templates. Based on the argument types provided explicitly or inferred from calls to this function, the compiler generates separate source-code functions (i.e., function-template specializations) to handle each function call appropriately. All function-template definitions begin with keyword `template` followed by a list of **template parameters** to the function template enclosed in angle brackets ( `<` and `>` ); each template parameter that represents a type must be preceded by either of the interchangeable keywords `class` or `typename` , as in

```c++
template< typename T >
// or
template< class ElementType >
// or
template< typename BorderType, typename FillType >
```

The type template parameters of a function-template definition are used to specify the types of the arguments to the function, to specify the return type of the function and to declare variables within the function. For example:

```c++
template< typename T >
T addNumbers( const T a, const T b )
{
  return ( a + b );
}
```

### Class Templates

Imagine the concept of a stack (a data structure in which we can store and retrieve data in *last-in first-out* order) independent of a storage type (generic). We can instantiate an object that is a type-specific version of this generic stack. For this purpose C++ provides class templates, also called **parametrized types**, because they require oner or more type parameters to specify the customization to form a class-template specialization. 

A class-template definition is preceded by a header

```c++
template< typename T >
```

to specify a class-template definition with **type parameter** `T` which acts as a placeholder for the type of the Stack class to be created.

For example:

```c++
template< typename T >
class Stack
{
  public:
  	Stack( int = 10 );
  	~Stack() { delete [] stackPtr; }
  	bool push( const T & );
  	bool pop( T & );
  	bool isEmpty() const { return top == -1; }
  	bool isFull() const { return top == size - 1; }
  private:
  	int size;
  	int top;
  	T *stackPtr;
};

template< typename T >
Stack< T >::Stack( int s ): 
		size( s > 0 ? s : 10 ), //validate size
		top( -1 ), // Stack initially empty
		stackPtr( new T[ size ] ) // allocate memory for elements
{ // empty body }

template< typename T >
bool Stack< T >::push( const T &pushValue )
{
  if ( !isFull() )
  {
  	stackPtr[ ++top ] = pushValue; // place item on Stack
  	return true; // push successful
  }
  return false; // push unsuccessful
}

template< typename T >
bool Stack< T >::pop( T &popValue )
{
  if ( !isEmpty() )
  {
    popValue = stackPtr[ top-- ]; // remove item from Stack
    return true; // pop successful
  }
  return false;
}
```

The member-function definitions of a class template are function templates. The member-function definitions that appear outside the class template definition each begin with the header

```c++
template< typename T >
```

The binary scope resolution operator is used with the class-template name `Stack< T >`  to tie each member-function definition to the class template’s scope.

### Class Template Specializations

Every object instantiation from a class template forms a specialization of it's generic definition. For example for an `Array` class template defined as

```c++
template<typename T>
class Array { };
```

an object instantiation like `Array< int > intArray;` creates a concrete form of the class template called **class-template specialization**. A number of specializations for a class template can be aliased using `typedef` statement in the header definition like

```c++
...
typedef Array< int > IntegerArray;
typedef Array< float > FloatArray;
typedef Array< double > DoubleArray;
```

C++ standard library defines many such `typedef`s for its class-template specializations. For example

```cpp
// class basic_string specialized for single byte character
typedef std::basic_string<char> std::string;
// class basic_string specialized for two byte (wide) character
typedef	std::basic_string<wchar_t> std::wstring;
```



### Nontype Parameters and Default Types

Class template declaration like `template< typename T > class Stack { };` use only a type parameter (T) in the header. It’s also possible to use non-type template parameters, which can have default arguments and are treated as `const`s. For example,

```c++
template< typename T, int elements > // nontype parameter elements
```

Then, a declaration such as

```c++
Stack< double, 100 > mostRecentSalesFigures;
```

could be used to instantiate (at compile time) a 100-element Stack *class-template specialization* of double values. The class definition then might contain a private data member with an array declaration such as

```c++
T stackHolder[ elements ]; // array to hold Stack contents
```

In addition, a type parameter can specify a **default type**. For example,

```c++
template< typename T = string > // defaults to type string
```

might specify that a `Stack` contains string objects by default. Then, a declaration such as

```c++
Stack<> jobDescriptions;
```

could be used to instantiate a `Stack` class-template specialization of `string` s. This class-template specialization would be of type `Stack< string >` .

### Class Template Specializations Summarized

Summarizing the syntax of class-template definitions:

```c++
// (1) defines a class template
template<typename T> class A { }; 

// (2) defines a class template explicit specialization 
template<> class A<int> { };

// (3) defines a class template partial specialization
template<typename T> class A<T*> { };

// (4) explicitly instantiates A<char>. 
template class A<char>;

// (5) implicitly instantiates A<short> (because of the member declaration)
struct D { A<short> a; };

// (6) defines a class template that defaults to type string
template< typename T = string > class Array { };
// defines a class template default type specialization
Array<> stringArray;

// (7) defines a class template with nontype parameter
template< typename T, int elements > Stack { };
// defines a specialization from a nontype parameter
Stack< double, 100 > mostRecentSalesFigures;

// (8) defines a class template with default valued nontype parameter
template< typename T, int elements = 10 > Stack { };
// defines a specialization with the default number of elements
Stack< string > recentPosts;
```



### Limitations of Templates prior to C++11

In order to understand *why* things are the way they are, first accept these facts:

1. A template is not a class or a function. A template is a “pattern” that the compiler uses to generate a family of [classes](https://isocpp.org/wiki/faq/templates#class-templates) or [functions](https://isocpp.org/wiki/faq/templates#fn-templates).
2. In order for the compiler to generate the code, it must see both the template definition (not just declaration) and the specific types/whatever used to “fill in” the template. For example, if you’re trying to use a `Foo<int>`, the compiler must see both the `Foo` template and the fact that you’re trying to make a specific `Foo<int>`.
3. Your compiler probably doesn’t remember the details of one `.cpp` file while it is compiling another `.cpp` file. It *could*, but most do not and if you are reading this FAQ, it almost definitely does not. BTW this is called the “**separate compilation model**”.

#### Template class can't define a default constructor

As type deduction doesn't work for default argument in template classes, the workaround is to define an extra constructor without any parameters. For example:

```c++
template<typename T>
class Foo
{
public:
  Foo() {
    // assign some default value
  }
  Foo(const T&);
  // ...

  private:
	  T value_;
};
```



#### Tell your compiler which instantiations to make while compiling

In case of syntax following standards prior to C++11, you need to tell your compiler which instantiations to make while it is compiling `.cpp` file defining your template function or class.

As an example, consider the header file `foo.h` which contains the following template function declaration:

```c++
// File "foo.h"
template<typename T>
extern void foo();
```

Now suppose file `foo.cpp` actually defines that template function:

```c++
// File "foo.cpp"
#include <iostream>
#include "foo.h"
template<typename T>
void foo()
{
  std::cout << "Here I am!\n";
}
```

Suppose file `main.cpp` uses this template function by calling `foo<int>()`:

```c++
// File "main.cpp"
#include "foo.h"
int main()
{
  foo<int>();
  // ...
}
```

If you compile and (try to) link these two `.cpp` files, most compilers will generate **linker errors**.

There are two solutions for this. 

1. physically move the definition of the template function into the .h file, even if it is not an `inline` function.

2. leave the definition of the template function in the .cpp file and simply add the line `template void foo<int>();` to that file. If you can’t modify `foo.cpp`, simply create a new `.cpp` file such as `foo-impl.cpp` as follows:

    ```c++
    // File "foo-impl.cpp"
    #include "foo.cpp"
    template void foo<int>();
    ```

    Notice that `foo-impl.cpp` `#include`s a `.cpp` file, not a `.h` file.

Since C++11 `extern template` becomes part of solution to this problem.

#### Defining global friend functions as function templates

The snag happens when the compiler sees the `friend` lines way up in the class definition proper. At that moment it does not yet know the `friend` functions are themselves templates; it assumes they are non-templates like this:

```c++
Foo<int> operator+ (const Foo<int>& lhs, const Foo<int>& rhs){ /*...*/ }
std::ostream& operator<< (std::ostream& o, const Foo<int>& x){ /*...*/ }
```

When you call the `operator+` or `operator<<` functions, this assumption causes the compiler to generate a call to the *non*-template functions, but the linker will give you an “undefined external” error because you never actually defined those *non*-template functions. The solution is to convince the compiler *while it is examining the class body proper* that the `operator+` and `operator<<` functions are themselves templates.

There are several ways to do this; one simple approach is to **pre-declare** each template friend function *above* the definition of template class `Foo`:

```c++
// pre-declare the template class itself
template<typename T> class Foo;
// pre-declare the friend functions
template<typename T> Foo<T> operator+ (const Foo<T>& lhs, const Foo<T>& rhs);
template<typename T> std::ostream& operator<< (std::ostream& o, const Foo<T>& x);
```

Also you add `<>` in the `friend` lines, as shown:

```c++
#include <iostream>
template<typename T>
class Foo
{
  public:
    Foo(const T& value = T());
    friend Foo<T> operator+ <> (const Foo<T>& lhs, const Foo<T>& rhs);
    friend std::ostream& operator<< <> (std::ostream& o, const Foo<T>& x);

  private:
	  T value_;
};
```

After the compiler sees that magic stuff, it will be better informed about the `friend` functions.

Another approach is to *define* the `friend` function within the class body at the same moment you declare it to be a `friend`. For example:

```c++
#include <iostream>
template<typename T>
class Foo {
public:
  Foo(const T& value = T());
  friend Foo<T> operator+ (const Foo<T>& lhs, const Foo<T>& rhs)
  {
    // ...
  }
  friend std::ostream& operator<< (std::ostream& o, const Foo<T>& x)
  {
    // ...
  }
private:
  T value_;
};
```



[^ Top](#Generic-Programming)



## References

1. [LearnCPP](https://www.learncpp.com/): Chapters# 8, 10, 14, 19
2. [ISOCPP FAQs on templates](https://isocpp.org/wiki/faq/templates)
3. [Why write the template class definition and declaration in the same .h file?](https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl)
4. [Should implementation be included in .h file?](https://www.bogotobogo.com/cplusplus/template_declaration_definition_header_implementation_file.php)
5. [How to avoid linker errors due to separate template function definition & declaration](https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl)
6. [How can I avoid linker errors with my template classes?](https://isocpp.org/wiki/faq/templates#separate-template-class-defn-from-decl)

