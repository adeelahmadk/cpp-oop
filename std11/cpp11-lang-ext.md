# C++11 Standard Language Extensions



## Contents

1. [General Features](#General-Features)
    1. [Type Deduction](#Type-Deduction)
    2. [decltype](#decltype)
    3. [Range-for statement](#Range-for-statement)
    4. [Initializer lists](#Initializer-lists)
    5. [Uniform initialization syntax and semantics](#Uniform-initialization-syntax-and-semantics)
    6. [Rvalue references and move semantics](#Rvalue-references-and-move-semantics)
    7. [Lambdas](#Lambdas)
    8. [`noexcept` to prevent exception propagation ](#noexcept-to-prevent-exception-propagation)
    9. [`constexpr`](#constexpr)
    10. [`nullptr` – a null pointer literal](#nullptr-a-null-pointer-literal)
    11. [Copying and rethrowing exceptions](#Copying-and-rethrowing-exceptions)
    12. [Inline namespaces](#Inline-namespaces)
    13. [User-defined literals](#User-defined-literals)
2. [Classes](#Classes)
    1. [`=default` and `=delete`](#=default-and-=delete )
    2. [Control of default move and copy](#Control-of-default-move-and-copy)
    3. [Delegating constructors](#Delegating-constructors)
    4. [In-class member initializers](#In-class-member-initializers)
    5. [Inherited constructors ](#Inherited-constructors)
    5. [Override controls: `override` ](#Override-controls-override)
    5. [Override controls: `final`](#Override-controls-final)
    5. [Explicit conversion operators](#Explicit-conversion-operators)
3. [Other Types](#Other-Types)
4. [Templates](#Templates)
5. [Concurrency](#Concurrency)
6. [Miscellaneous Language Features](#Miscellaneous-Language-Features)
7. [General Libraries](#General-Libraries)
8. [Containers and Algorithms](#Containers-and-Algorithms)
9. [Library Concurrency](#Library-Concurrency)
10. [References](#References)



## General Features

### Type Deduction


Consider
```cpp
auto x = 7;
```

Here x will have the type int because that’s the type of its initializer. In general, we can write


```cpp
auto x = expression;
```
and the type of x will be the type of the value computed from “expression”.

The use of auto to deduce the type of a variable from its initializer is obviously most useful when that type is either hard to know exactly or hard to write. Consider:

```cpp
template<class T> void printall(const vector<T>& v)
{
  for (auto p = v.begin(); p!=v.end(); ++p)
    cout << *p << "\n";
}
```
In C++98, we’d have to write

```cpp
template<class T> void printall(const vector<T>& v)
{
    for (typename vector<T>::const_iterator p = v.begin(); p!=v.end(); ++p)
        cout << *p << "\n";
}
```

When the type of a variable depends critically on template argument it can be really hard to write code without auto. For example:
```cpp
template<class T, class U> void multiply(const vector<T>& vt, const vector<U>& vu)
{
  // ...
  auto tmp = vt[i]*vu[i];
  // ...
}
```
The type of tmp should be what you get from multiplying a T by a U, but exactly what that is can be hard for the human reader to figure out, though of course the compiler knows once it has figured out what particular T and U it is dealing with.

The old meaning of auto (namely “this is a local variable”) is now illegal.


### decltype  

decltype(E) is the type (“declared type”) of the name or expression E and can be used in declarations. For example:

```cpp
void f(const vector<int>& a, vector<float>& b)
{
  typedef decltype(a[0]*b[0]) Tmp;
  for (int i=0; i<b.size(); ++i) {
    Tmp* p = new Tmp(a[i]*b[i]);
    // ...
  }
  // ...
}
```

This notion has been popular in generic programming under the label “typeof” for a long time, but the “typeof” implementations in actual use were incomplete and incompatible, so the standard version is named decltype.

### Range-for statement 
A range for statement allows you to iterate through a “range”, which is anything you can iterate through like an STL-sequence defined by a begin() and end(). All standard containers can be used as a range, as can a std::string, an initializer list, an array, and anything for which you define begin() and end(), e.g. an istream. For example:

```
void f(vector<double>& v)
{
  for (auto x : v) cout << x << '\n';
  for (auto& x : v) ++x;  // using a reference to allow us to change the value
}
```

You can read that as “for all x in v” going through starting with v.begin() and iterating to v.end(). Another example:

```cpp
for (const auto x : { 1,2,3,5,8,13,21,34 }) cout << x << '\n';
```

The begin() (and end()) can be a member to be called as x.begin() or a free-standing function to be called as begin(x). The member version takes precedence.

### Initializer lists  

Consider
```cpp
vector<double> v = { 1, 2, 3.456, 99.99 };
list<pair<string,string>> languages = {
    {"Nygaard","Simula"}, {"Richards","BCPL"}, {"Ritchie","C"}
}; 
map<vector<string>,vector<int>> years = {
    { {"Maurice","Vincent", "Wilkes"},{1913, 1945, 1951, 1967, 2000} },
    { {"Martin", "Ritchards"}, {1982, 2003, 2007} }, 
    { {"David", "John", "Wheeler"}, {1927, 1947, 1951, 2004} }
}; 
```

Initializer lists are not just for arrays any more. The mechanism for accepting a {}-list is a function (often a constructor) accepting an argument of type std::initializer_list<T>. For example:
```cpp
void f(initializer_list<int>);
f({1,2});
f({23,345,4567,56789});
f({});  // the empty list
f{1,2}; // error: function call ( ) missing
years.insert({{"Bjarne","Stroustrup"},{1950, 1975, 1985}});
```

The initializer list can be of arbitrary length, but must be homogeneous (all elements must be of the template argument type, T, or convertible to T).
A container might implement an initializer-list constructor like this:
```cpp
template<class E> class vector {
public:
    vector (std::initializer_list<E> s) // initializer-list constructor
    {
            reserve(s.size());  // get the right amount of space
            uninitialized_copy(s.begin(), s.end(), elem);   // initialize elements (in elem[0:s.size()))
        sz = s.size();  // set vector size
    }
    // ... as before ...
};
```

The distinction between direct initialization and copy initialization is maintained for {}-initialization, but becomes relevant less frequently because of {}-initialization. For example, std::vector has an explicit constructor from int and an initializer_list constructor:
```cpp
vector<double> v1(7);   // ok: v1 has 7 elements
v1 = 9;                 // error: no conversion from int to vector
vector<double> v2 = 9;  // error: no conversion from int to vector
void f(const vector<double>&);
f(9);                           // error: no conversion from int to vector
vector<double> v1{7};           // ok: v1 has 1 element (with its value 7.0)
v1 = {9};                       // ok v1 now has 1 element (with its value 9.0)
vector<double> v2 = {9};        // ok: v2 has 1 element (with its value 9.0)
f({9});                         // ok: f is called with the list { 9 }
vector<vector<double>> vs = {
    vector<double>(10),         // ok: explicit construction (10 elements)
    vector<double>{10},         // ok explicit construction (1 element with the value 10.0)
    10                          // error: vector's constructor is explicit
};  
```

The function can access the initializer_list as an immutable sequence. For example:
```cpp
void f(initializer_list<int> args)
{
  for (auto p=args.begin(); p!=args.end(); ++p) cout << *p << "\n";
}
```

A constructor that takes a single argument of type std::initializer_list is called an initializer-list constructor.

The standard library containers, string, and regex have initializer-list constructors, assignment, etc. An initializer-list can be used as a range, e.g. in a range for statement.

### Uniform initialization syntax and semantics  

C++98 offers several ways of initializing an object depending on its type and the initialization context. When misused, the error can be surprising and the error messages obscure. Consider:
```cpp
string a[] = { "foo", " bar" };          // ok: initialize array variable
vector<string> v = { "foo", " bar" };    // error: initializer list for non-aggregate vector
void f(string a[]);
f( { "foo", " bar" } );                  // syntax error: block as argument
```

and
```cpp
int a = 2;              // "assignment style"
int aa[] = { 2, 3 };    // assignment style with list
complex z(1,2);         // "functional style" initialization
x = Ptr(y);             // "functional style" for conversion/cast/construction
```

and
```cpp
int a(1);   // variable definition
int b();    // function declaration
int b(foo); // variable definition or function declaration
```

It can be hard to remember the rules for initialization and to choose the best way.

The C++11 solution is to allow {}-initializer lists for all initialization:
```cpp
X x1 = X{1,2}; 
X x2 = {1,2};   // the = is optional
X x3{1,2}; 
X* p = new X{1,2}; 
struct D : X {
  D(int x, int y) :X{x,y} { /* ... */ };
};
struct S {
  int a[3];
  S(int x, int y, int z) :a{x,y,z} { /* ... */ }; // solution to old problem
};
```

Importantly, X{a} constructs the same value in every context, so that {}-initialization gives the same result in all places where it is legal. For example:
```cpp
X x{a}; 
X* p = new X{a};
z = X{a};         // use as cast
f({a});           // function argument (of type X)
return {a};       // function return value (function returning X)
```

C++11 uniform initialization is not perfectly uniform, but it’s very nearly so. C++11’s {} initialization syntax and semantics provide a much simpler and consistent way to perform initialization, that is also more powerful (e.g., `vector<int> v = { 1, 2, 3, 4 }`) and safer (e.g., {} does not allow narrowing conversions). Prefer initializing using {}.

### Rvalue references and move semantics 

The concepts of `lvalues` (what can be used on the left-hand side  of an assignment) and `rvalues` (what can be used on the right-hand side  of an assignment) in C++ are inherited from CPL. In C++98, references to non-`const` can bind to `lvalues` and references to `const` can bind to `lvalues` or `rvalues`, but there is nothing that can bind to a non-`const` `rvalue`.

That’s to protect people from changing the values of temporaries that are destroyed before their new value can be used. For example:

```cpp
void incr(int& a) { ++a; }
int i = 0;
incr(i);    // i becomes 1
incr(0);    // error: 0 in not an lvalue
```

So far, so good, but consider

```cpp
template<class T> swap(T& a, T& b)      // "old style swap"
{
  T tmp(a);   // now we have two copies of a
  a = b;      // now we have two copies of b
  b = tmp;    // now we have two copies of tmp (aka a)
} 
```

If `T` is a type for which it can be expensive to copy elements, such as `string` and `vector`, `swap` becomes an expensive operation. Note something curious: **We didn’t want any copies at all**. We just wanted to move the values of `a`, `b`, and `tmp` around a bit.

In C++11, we can define “**move constructors**” and “**move assignments**” to move rather than copy their argument:

```cpp
template<class T> class vector {
  // ...
  vector(const vector&);          		// copy constructor
  vector(vector&&);           				// move constructor
  vector& operator=(const vector&);   // copy assignment
  vector& operator=(vector&&);        // move assignment
};  // note: move constructor and move assignment takes non-const &&
// they can, and usually do, write to their argument
```

The `&&` indicates an “**rvalue reference**”. An `rvalue` reference can bind to an `rvalue` (but not to an `lvalue`):

```cpp
X a;
X f();
X& r1 = a;      // bind r1 to a (an lvalue)
X& r2 = f();    // error: f() is an rvalue; can't bind
X&& rr1 = f();  // fine: bind rr1 to temporary
X&& rr2 = a;    // error: bind a is an lvalue
```

The idea behind a move assignment is that *instead of making a copy, it simply takes the representation from its source and replaces it with a cheap default*. For example, for `string`s `s1=s2` using the move assignment would not make a copy of `s2`’s characters; instead, it would just let `s1` treat those characters as its own and somehow delete `s1`’s old characters (maybe by leaving them in `s2`, which presumably is just about to be destroyed).

How do we know whether it’s ok to simply move from a source? We tell the compiler:

```cpp
template<class T>
void swap(T& a, T& b)   // "perfect swap" (almost)
{
  T tmp = move(a);    // could invalidate a
  a = move(b);        // could invalidate b
  b = move(tmp);      // could invalidate tmp
}
```

`move(x)` is *just a cast* that means “you can treat `x` as an `rvalue`”. Maybe it would have been better if `move()` had been called `rval()`, but by now `move()` has been used for years. The `move()` template function can be written in C++11 (see the “brief introduction”) and and uses `rvalue` references.

`rvalue` references can also be used to provide perfect forwarding.

In the C++11 standard library, all containers are provided with move  constructors and move assignments, and operations that insert new  elements, such as `insert()` and `push_back()`,  have versions that take rvalue references. The net result is that the  standard containers and algorithms quietly – without user intervention – improve in performance because they copy less.



### Lambdas

A lambda expression is a mechanism for specifying a function object. The primary use for a lambda is to specify a simple action to be performed by some function. For example:

```cpp
vector<int> v = {50, -10, 20, -30};
std::sort(v.begin(), v.end());  // the default sort
// now v should be { -30, -10, 20, 50 }

// sort by absolute value:
std::sort(v.begin(), v.end(), [](int a, int b) { return abs(a)<abs(b); });
// now v should be { -10, 20, -30, 50 }
```

The argument `[](int a, int b) { return abs(a)<abs(b); }` is a “lambda” (or “lambda function” or “lambda expression”), which specifies an operation that given two integer arguments `a` and `b` returns the result of comparing their absolute values.

A lambda expression can access local variables in the scope in which it is used. For example:

```cpp
void f(vector<Record>& v)
{
  vector<int> indices(v.size());
  int count = 0;
  std::generate(indices.begin(), indices.end(), [&count](){ return count++; });
  
  // sort indices in the order determined by the name field of the records:        
  std::sort(
    indices.begin(),
    indices.end(),
    [&](int a, int b) { return v[a].name<v[b].name; }
  );
  // ...
}
```

Some consider this “really neat!”; others see it as a way to write dangerously obscure code. Both are right.

Functions `generate` and `sort` are from C++ STL header `algorithm`. The `generate` function is prototyped as

```cpp
template< class ForwardIt, class Generator >
void generate( ForwardIt first, ForwardIt last, Generator g );
```

It assigns each element in range `[`first`, `last`)` a value generated by the given function object g.

The `[&]` is a “capture list” specifying that local names used will be passed by reference. Had we wanted to “capture” only `v`, we could have said so: `[&v]`. Had we wanted to pass `v` by value, we could have said so: `[=v]` or `[v]`. Capture nothing is `[]`, capture all by reference is `[&]`, and capture all by value is `[=]`.

If an action is neither common nor simple, consider using a named function object or function. For example, the example above could have been written:

```cpp
void f(vector<Record>& v)
{
  vector<int> indices(v.size());
  int count = 0;
  generate(indices.begin(),indices.end(),[&](){ return ++count; });
  struct Cmp_names {
    const vector<Record>& vr;
    Cmp_names(const vector<Record>& r) :vr(r) { }
    bool operator()(int a, int b) const { return vr[a].name<vr[b].name; }
  };
  
  // sort indices in the order determined by the name field of the records:        
  std::sort(indices.begin(), indices.end(), Cmp_names(v));
  // ...
}
```

For a tiny function, such as this `Record` name field comparison, the function object notation is verbose, though the  generated code is likely to be identical. In C++98, such function  objects had to be non-local to be used as template argument; in C++ [this is no longer necessary](https://isocpp.org/wiki/faq/cpp11-language-templates#local-types).

To specify a lambda you must provide

- Its capture list: the list of variables it can use (in addition to its arguments), if any (`[&]` meaning “all local variables passed by reference” in the Record comparison example). If no names need to be captured, a lambda starts with plain `[]`. 
- (optionally) Its arguments and their types (e.g, `(int a, int b)`) 
- The action to be performed as a block (e.g., `{ return v[a].name<v[b].name; }`). 
- (optionally) The return type using the new [suffix return type syntax](https://isocpp.org/wiki/faq/cpp11-language-misc#suffix-return); but typically we just deduce the return type from the `return` statement. If no value is returned then `void` is deduced. 



### noexcept to prevent exception propagation 

If a function cannot throw an exception or if the program isn’t written to handle exceptions thrown by a function, that function can be declared `noexcept`. For example:

```cpp
extern "C" double sqrt(double) noexcept;    // will never throw
vector<double> my_computation(const vector<double>& v) noexcept // I'm not prepared to handle memory exhaustion
{
  vector<double> res(v.size());   // might throw
  for(int i; i < v.size(); ++i) res[i] = sqrt(v[i]);
  return res;
}
```

If a function declared `noexcept` throws (so that the exception tries to escape the `noexcept` function) the program is terminated by a call to `std::terminate()`. The call of `terminate()` cannot rely on objects being in well-defined states; that is, there is no guarantee that destructors have been invoked, no guaranteed stack unwinding, and no possibility for resuming the program as if no problem had been encountered. This is deliberate and makes `noexcept` a simple, crude, and very efficient mechanism – much more efficient than the old dynamic `throw()` exception specification mechanism.

It is possible to make a function conditionally `noexcept`. For example, an algorithm can be specified to be `noexcept` if (and only if) the operations it uses on a template argument are `noexcept`:

```cpp
template<class T>
void do_f(vector<T>& v) noexcept(noexcept(f(v.at(0)))) // can throw if f(v.at(0)) can
{
  for(int i; i<v.size(); ++i)
    v.at(i) = f(v.at(i));
}
```

Here, we first use `noexcept` as an operator: `noexcept(f(v.at(0)))` is true if `f(v.at(0))` can’t throw, that is if the `f()` and `at()` used are `noexcept`.

The `noexcept()` operator is a constant expression and does not evaluate its operand.

The general form of a `noexcept` declaration is `noexcept(expression)` and “plain `noexcept`” is simply a shorthand for `noexcept(true)`. All declarations of a function must have compatible `noexcept` specifications.

A destructor shouldn’t throw; a generated destructor is implicitly `noexcept` (independently of what code is in its body) if all of the members of its class have `noexcept` destructors (which, ahem, they too will have by default).

It is typically a bad idea to have a move operation throw, so declare those `noexcept` wherever possible. A generated copy or move operation is implicitly `noexcept` if all of the copy or move operations it uses on members of its class have `noexcept` destructors.

`noexcept` is widely and systematically used in the standard library to improve performance and clarify requirements.



### constexpr

The `constexpr` mechanism

- provides more general constant expressions 
- allows constant expressions involving user-defined types 
- provides a way to guarantee that an initialization is done at compile time 

Consider

```cpp
enum Flags { good=0, fail=1, bad=2, eof=4 };
constexpr int operator|(Flags f1, Flags f2) { return Flags(int(f1)|int(f2)); }
void f(Flags x)
{
  switch (x) {
    case bad:         /* ... */ break;
    case eof:         /* ... */ break;
    case bad|eof:     /* ... */ break;
    default:          /* ... */ break;
  }
}
```

Here `constexpr` says that the function must be of a simple form so that it can be evaluated at compile time if given constant expressions arguments.

In addition to be able to evaluate expressions at compile time, we want to be able to require expressions to be evaluated at compile time; `constexpr` in front of a variable definition does that (and implies `const`):

```cpp
constexpr int x1 = bad|eof; // ok
void f(Flags f3)
{
  constexpr int x2 = bad|f3;  // error: can't evaluate at compile time
  int x3 = bad|f3;        // ok
}
```

Typically we want the compile-time evaluation guarantee for global or namespace objects, often for objects we want to place in read-only  storage.

This also works for objects for which the constructors are simple enough to be `constexpr` and expressions involving such objects:

```cpp
struct Point {
  int x,y;
  constexpr Point(int xx, int yy) : x(xx), y(yy) { }
};
constexpr Point origo(0,0);
constexpr int z = origo.x;
constexpr Point a[] = {Point(0,0), Point(1,1), Point(2,2) };
constexpr int x = a[1].x;   // x becomes 1
```

Please note that `constexpr` is not a general purpose replacement for `const` (or vice versa):

- `const`’s primary function is to express the idea that an object is not modified through an interface (even though the object may very well be modified through other interfaces). It just so happens that declaring an object `const` provides excellent optimization opportunities for the compiler. In particular, if an object is declared `const` and its address isn’t taken, a compiler is often able to evaluate its  initializer at compile time (though that’s not guaranteed) and keep that object in its tables rather than emitting it into the generated code. 
- `constexpr`’s primary function is to extend the range of what can be computed at compile time, making such computation type safe and also usable in compile-time contexts (such as to initialize enumerator or integral template parameters). Objects declared `constexpr` have their initializer evaluated at compile time; they are basically values kept in the compiler’s tables and only emitted into the generated code if needed.



### nullptr a null pointer literal

`nullptr` is a literal denoting the null pointer; it is not an integer:

```cpp
char* p = nullptr;
int* q = nullptr;
char* p2 = 0;           // 0 still works and p==p2

void f(int);
void f(char*);

f(0);                   // call f(int)
f(nullptr);             // call f(char*)

void g(int);
g(nullptr);             // error: nullptr is not an int
int i = nullptr;        // error: nullptr is not an int
```



### Copying and rethrowing exceptions 

How do you catch an exception and then rethrow it on another thread?  Use a bit of library magic as described in the standard 18.8.5 Exception Propagation:

- `exception_ptr current_exception();` Returns: An `exception_ptr` object that refers to the currently handled exception (15.3) or a copy of the currently handled exception, or a null `exception_ptr` object if no exception is being handled. The referenced object shall remain valid at least as long as there is an `exception_ptr` object that refers to it. …  
- `void rethrow_exception(exception_ptr p);` 
- `template<class E> exception_ptr copy_exception(E e);` Effects: as if 

```cpp
try {
  throw e;
} catch(...) {
  return current_exception();
}
```

This is particularly useful for [transmitting an exception from one thread to another](https://isocpp.org/wiki/faq/cpp11-library-concurrency#cpp11-future).

### Inline namespaces 

The `inline namespace` mechanism is intended to support library evolution by providing a mechanism that supports a form of versioning. Consider:

```cpp
// file V99.h:
inline namespace V99 {
  void f(int);    // does something better than the V98 version
  void f(double); // new feature
  // ...
}

// file V98.h:
namespace V98 {
  void f(int);    // does something
  // ...
}

// file Mine.h:
namespace Mine {
#include "V99.h"
#include "V98.h"
}
```

We here have a namespace `Mine` with both the latest release (`V99`) and the previous one (`V98`). If you want to be specific, you can:

```cpp
    #include "Mine.h"    using namespace Mine;    // ...    V98::f(1);  // old version    V99::f(1);  // new version    f(1);       // default version
```

The point is that the `inline` specifier makes the  declarations from the nested namespace appear exactly as if they had  been declared in the enclosing namespace.

This is a very “static” and implementer-oriented facility in that the `inline` specifier has to be placed by the designer of the namespaces – thus  making the choice for all users. It is not possible for a user of `Mine` to say “I want the default to be `V98` rather than `V99`.”



### User-defined literals 

C++ has always provided literals for a variety of built-in types (2.14 Literals):

```cpp
123 		// int
1.2 		// double
1.2F    // float
'a' 		// char
1ULL    // unsigned long long
0xD0    // hexadecimal unsigned
"as"    // string
```

However, in C++98 there are no literals for user-defined types. This  can be a bother and also seen as a violation of the principle that user-defined types should be supported as well as built-in types are. In particular, people have requested:

```cpp
"Hi!"s          // std::string, not ``zero-terminated array of char''
1.2i            // imaginary
123.4567891234df    // decimal floating point (IBM)
101010111000101b    // binary
123s            // seconds
123.56km        // not miles! (units)
1234567890123456789012345678901234567890x   // extended-precision
```

C++11 supports “user-defined literals” through the notion of literal  operators that map literals with a given suffix into a desired type. For example:

```cpp
constexpr complex<double> operator "" i(long double d)  // imaginary literal
{
  return {0,d};   // complex is a literal type
}

std::string operator""s (const char* p, size_t n)   // std::string literal
{
  return string(p,n); // requires free store allocation
}
```

Note the use of `constexpr` to enable compile-time evaluation. Given those, we can write

```cpp
template<class T> void f(const T&);
f("Hello"); // pass pointer to char*
f("Hello"s);    // pass (5-character) string object
f("Hello\n"s);  // pass (6-character) string object
auto z = 2+1i;  // complex(2,1)
```

The basic (implementation) idea is that after parsing what could be a literal, the compiler always checks for a suffix. The user-defined  literal mechanism simply allows the user to specify a new suffix and  what is to be done with the literal before it. It is not possible to  redefine the meaning of a built-in literal suffix or augment the syntax  of literals. A literal operator can request to get its (preceding)  literal passed “cooked” (with the value it would have had if the new  suffix hadn’t been defined) or “uncooked” (as a string).

To get an “uncooked” string, simply request a single `const char*` argument:

```cpp
Bignum operator"" x(const char* p)
{
  return Bignum(p);
}
void f(Bignum);
f(1234567890123456789012345678901234567890x);
```

Here the C-style string `"1234567890123456789012345678901234567890"` is passed to `operator"" x()`. Note that we did not explicitly put those digits into a string.

There are four kinds of literals that can be suffixed to make a user-defined literal.

- **Integer literal**: accepted by a literal operator taking a single `unsigned long long` or `const char*` argument. 
- **Floating-point literal**: accepted by a literal operator taking a single `long double` or `const char*` argument. 
- **String literal**: accepted by a literal operator taking a pair of (`const char*`, `size_t`) arguments.
- **Character literal**: accepted by a literal operator taking a single `char` argument. 

Note that you cannot make a literal operator for a string literal that takes just a `const char*` argument (and no size). For example:

```cpp
string operator"" S(const char* p);     // warning: this will not work as expected
"one two"S; // error: no applicable literal operator
```

The rationale is that _if we want to have “a different kind of string” we almost always want to know the number of characters_ anyway.

Suffixes will tend to be short (e.g. `s` for `string`, `i` for imaginary, `m` for meter, and `x` for extended), so different uses could easily clash. Use namespaces to prevent clashes:

```cpp
namespace Numerics {
  // ...
  class Bignum { /* ... */ };
  namespace literals {
    operator"" X(char const*);
  }
}
using namespace Numerics::literals; 
```



## Classes



### =default and =delete 

The common idiom of “prohibiting copying” can now be expressed directly:

```cpp
class X {
  // ...
  X& operator=(const X&) = delete;    // Disallow copying operation
  X(const X&) = delete;		// Disallow copy constructor
};
```

The C++ 11 standard introduced another use of `delete` operator, which is: **To disable the usage of a member function.** This is done by appending the **=delete;** specifier to the end of that function declaration.
Any member function whose usage has been disabled by using the ‘=delete’ specifier is known as an explicitly **deleted function.**

Some useful examples are:

1. **Disabling copy constructors**

```cpp
class A {
public:
    A(int x): m(x)
    {
    }
     
    // Delete the copy constructor
    A(const A&) = delete;
     
    // Delete the copy assignment operator
    A& operator=(const A&) = delete;
    int m;
};
 
int main()
{
    A a1(1), a2(2), a3(3);
     
    // Error, the usage of the copy
    // assignment operator is disabled
    a1 = a2;
     
    // Error, the usage of the
    // copy constructor is disabled
    a3 = A(a2);
    return 0;
}
```

2. **Disabling undesirable argument conversion** 

```cpp
// Disable undesirable argument type conversion
// using delete operator
class A {
public:
	A(int) {}

	// Declare the conversion constructor as a
	// deleted function. Without this step,
	// even though A(double) isn't defined,
	// the A(int) would accept any double value
	// for it's argumentand convert it to an int
	A(double) = delete;
};

int main()
{
	A A1(1);
	
	// Error, conversion from
	// double to class A is disabled.
	A A2(100.1);
	return 0;
}
```

The main advantages of explicitly deleting functions:

1. Deleting special member functions provides a cleaner way of  preventing the compiler from generating special member functions that we don’t want.

2. Deleting normal member function or non-member functions prevents problematic type promotions from causing an unintended function to be called 

Conversely, we can also say explicitly that we want the default copy behavior:

```cpp
class Y {
  // ...
  Y& operator=(const Y&) = default;   // default copy semantics
  Y(const Y&) = default;
};
```

Explicitly defaulted function declaration allows appending `=default` specifier to declare that function as an explicitly defaulted function. This makes the compiler generate the default implementations for explicitly defaulted functions, which are more efficient than manually programmed function implementations. 

For example, whenever we declare a parameterized constructor, the  compiler won’t create a default constructor. In such a case, we can use  the default specifier in order to create a default one.

A defaulted function needs to be a **special member function** (default  constructor, copy constructor, destructor etc), or has no default  arguments.

```cpp
class B {
public:
 
    // Error, func is not a special member function.
    int func() = default;
     
    // Error, constructor B(int, int) is not
    // a special member function.
    B(int, int) = default;
 
    // Error, constructor B(int=0)
    // has a default argument.
    B(int = 0) = default;
};
```

Explicitly writing out the default by hand is at best redundant, and  has two drawbacks: it sometimes generates less efficient code than the  compiler-generated default would, and it prevents types from being  considered PODs (plain old data types). However, comments about copy operations and (worse) a  user explicitly defining copy operations meant to give the default  behavior were not uncommon in pre-C++11 code. Leaving it to the compiler to implement the default behavior is simpler, less error-prone, and  often leads to better object code.

The `=default` mechanism can be used for any function that has a default. The `=delete` mechanism can be used for any function. For example, we can eliminate an undesired conversion like this:

```cpp
struct Z {
  // ...
  Z(long long);     // can initialize with a long long
  Z(long) = delete; // but not anything smaller
};
```



### Control of default move and copy 

By default, a class has five operations:

- copy assignment 
- copy constructor 
- move assignment 
- move constructor 
- destructor

If you declare any of those you must consider all and explicitly define or `=default` the ones you want. Think of copying, moving, and destruction as closely related operations, rather than individual operations that you can  freely mix and match – you can specify arbitrary combinations, but only a few combinations make sense semantically.

If any move, copy, or destructor is explicitly specified (declared, defined, `=default`, or `=delete`) by the user, no move is generated by default. If any copy or destructor is explicitly specified (declared, defined, `=default`, or `=delete`) by the user, any undeclared copy operations are generated by default,  but this is deprecated, so don’t rely on that. For example:

```cpp
class X1 {
  X1& operator=(const X1&) = delete;  // Disallow copying
};
```

This implicitly also disallows moving of `X1`s. Copy initialization is allowed, but deprecated.

```cpp
class X2 {
  X2& operator=(const X2&) = default;
};
```

This implicitly also disallows moving of `X2`s. Copy initialization is allowed, but deprecated.

```cpp
class X3 {
  X3& operator=(X3&&) = delete;   // Disallow moving
}
```

This implicitly also disallows copying of `X3`s.

```cpp
class X4 {
  ~X4() = delete; // Disallow destruction    }
```

This implicitly also disallows moving of `X4`s. Copying is allowed, but deprecated.

If you declare one of these five function, you should explicitly declare all. For example:

```cpp
template<class T>
class Handle {
  T* p;
  public:
  Handle(T* pp) : p{pp} {}
  ~Handle() { delete p; }     // user-defined destructor: no implicit copy or move
  Handle(Handle&& h) :p{h.p} { h.p=nullptr; }     // transfer ownership
  Handle& operator=(Handle&& h) { delete p; p=h.p; h.p=nullptr; return *this; }   // transfer ownership
  Handle(const Handle&) = delete;     // no copy
  Handle& operator=(const Handle&) = delete;
  // ... 
};
```



### Delegating constructors 

In C++98, if you want two constructors to do the same thing, repeat yourself or call "an `init()` function." For example:

```cpp
class X {
  int a;
  void validate(int x) { if (0<x && x<=max) a=x; else throw bad_X(x); }
public:
  X(int x) { validate(x); }
  X() { validate(42); }
  X(string s) { int x = lexical_cast<int>(s); validate(x); }
  // ...
};
```

Verbosity hinders readability and repetition is error-prone. Both get in the way of maintainability. So, in C++11, we can define one constructor in terms of another:

```cpp
class X {
  int a;
public:
  X(int x) { if (0<x && x<=max) a=x; else throw bad_X(x); }
  X() :X{42} { }
  X(string s) :X{lexical_cast<int>(s)} { }
  // ...
};
```



### In-class member initializers 

In C++98, only `static const` members of integral types could be initialized in-class, and the initializer has to be a constant expression. These restrictions ensured that the compiler can do the initialization at compile-time. For example:

```cpp
int var = 7;
class X {
  static const int m1 = 7;        // ok
  const int m2 = 7;               // error: not static
  static int m3 = 7;              // error: not const
  static const int m4 = var;      // error: initializer not constant expression
  static const string m5 = "odd"; // error: not integral type
  // ...
};
```

The basic idea for C++11 was to allow a non-static data member to be  initialized where it is declared (in its class). A constructor can then use the initializer when run-time initialization is needed. Consider:

```cpp
class A {
public:
  int a = 7;
};
```

This is equivalent to:

```cpp
class A {
public:
  int a;
  A() : a(7) {}
};
```

This saves a bit of typing, but the real benefits come in classes  with multiple constructors. Often, all constructors use a common  initializer for a member:

```cpp
class A {
public:
  A(): a(7), b(5), hash_algorithm("MD5"), s("Constructor run") {}
  A(int a_val) : a(a_val), b(5), hash_algorithm("MD5"), s("Constructor run") {}
  A(D d) : a(7), b(g(d)), hash_algorithm("MD5"), s("Constructor run") {}
  int a, b;
private:
  HashingFunction hash_algorithm;  // Cryptographic hash to be applied to all A instances
  std::string s;                   // String indicating state in object lifecycle
};
```

The fact that `hash_algorithm` and `s` each have a single default is lost in the mess of code and could easily become a problem during maintenance. Instead, we can factor out the initialization of the data members:

```cpp
class A {
public:
  A(): a(7), b(5) {}
  A(int a_val) : a(a_val), b(5) {}
  A(D d) : a(7), b(g(d)) {}
  int a, b;
private:
  HashingFunction hash_algorithm{"MD5"};  // Cryptographic hash to be applied to all A instances
  std::string s{"Constructor run"};       // String indicating state in object lifecycle
};
```

If a member is initialized by both an in-class initializer and a  constructor, only the constructor’s initialization is done (it "overrides" the default). So we can simplify further:

```cpp
class A {
public:
  A() {}
  A(int a_val) : a(a_val) {}
  A(D d) : b(g(d)) {}
  int a = 7;
  int b = 5;
private:
  HashingFunction hash_algorithm{"MD5"};  // Cryptographic hash to be applied to all A instances
  std::string s{"Constructor run"};       // String indicating state in object lifecycle
};
```



### Inherited constructors 

People sometimes are confused about the fact that ordinary scope  rules apply to class members. In particular, a member of a base class is not in the same scope as a member of a derived class:

```cpp
struct B {
  void f(double);
};
struct D : B {
  void f(int);
};
B b;
b.f(4.5);    // fine
D d;
d.f(4.5);    // surprise: calls f(int) with argument 4
```

In C++98, we can "lift" a set of overloaded functions from a base class into a derived class:

```cpp
struct B {
  void f(double);
};
struct D : B {
  using B::f;     // bring all f()s from B into scope
  void f(int);    // add a new f()
};
B b;
b.f(4.5);    // fine
D d;
d.f(4.5);    // fine: calls D::f(double) which is B::f(double)
```

Stroustrup has said that “Little more than a historical accident prevents using this to work for a constructor as well as for an ordinary member function.” C++11 provides that facility:

```cpp
class Derived : public Base {
public:
  using Base::f;    // lift Base's f into Derived's scope -- works in C++98
  void f(char);     // provide a new f
  void f(int);      // prefer this f to Base::f(int)
  using Base::Base; // lift Base constructors into Derived's scope -- new in C++11
  Derived(char);    // provide a new constructor
  Derived(int);     // prefer this constructor to Base::Base(int)
  // ...
}; 
```

If you so choose, you can still _shoot yourself in the foot_ by inheriting constructors in a derived class in which you define new member variables needing initialization:

```cpp
struct B1 {
  B1(int) { }
};
struct D1 : B1 {
  using B1::B1; // implicitly declares D1(int)
  int x;
};

void test()
{
  D1 d(6);    // Oops: d.x is not initialized
  D1 e;       // error: D1 has no default constructor
}
```

You might remove the bullet from your foot by using a [member-initializer](https://isocpp.org/wiki/faq/cpp11-language-classes#member-init):

```cpp
struct D1 : B1 {
  using B1::B1;   // implicitly declares D1(int)
  int x{0};   		// note: x is initialized
};

void test()
{
  D1 d(6);    // d.x is zero
}
```



### Override controls: override 

No special keyword or annotation is needed for a function in a  derived class to override a function in a base class. For example:

```cpp
struct B {
  virtual void f();
  virtual void g() const;
  virtual void h(char);
  void k();   // not virtual
};

struct D : B {
  void f();   // overrides B::f()
  void g();   // doesn't override B::g() (wrong type)
  virtual void h(char);   // overrides B::h()
  void k();   // doesn't override B::k() (B::k() is not virtual)
};
```

This can cause confusion (what did the programmer mean?), and  problems if a compiler doesn’t warn against suspicious code. For  example,

- Did the programmer mean to override `B::g()`? (almost certainly yes). 
- Did the programmer mean to override `B::h(char)`? (probably not because of the redundant explicit `virtual`). 
- Did the programmer mean to override `B::k()`? (probably, but that’s not possible). 

To allow the programmer to be more explicit about overriding, we now have the "contextual keyword" `override`:

```cpp
struct D : B {
  void f() override;  // OK: overrides B::f()
  void g() override;  // error: wrong type
  virtual void h(char);   // overrides B::h(); likely warning
  void k() override;  // error: B::k() is not virtual    };
```

A declaration marked `override` is only valid if there is a function to override. The problem with `h()` is not guaranteed to be caught (because it is not an error according to the language definition) but it is easily diagnosed.

`override` is only a contextual keyword, so you can still use it as an identifier:

```cpp
int override = 7;   // not recommended
```



### Override controls: final 

Sometimes, a programmer wants to prevent a virtual function from being overridden. This can be achieved by adding the specifier `final`. For example:

```cpp
struct B {
  virtual void f() const final;   // do not override
  virtual void g();
};

struct D : B {
  void f() const;     // error: D::f attempts to override final B::f
  void g();       // OK
};
```

There are _legitimate reasons_ for wanting to prevent overriding, but it should be noted that many examples used to motivate `final` have been based on mistaken assumptions on how expensive virtual  functions are (usually based on experience with other languages). So, if you feel the urge to add a `final` specifier, please double check that the reason is logical: Would semantic errors be likely if someone defined a class that overrode that virtual function? Adding `final` closes the possibility that a future user of the class might provide a better implementation of the function for some class you haven’t thought of. _If you don’t want to keep that option open, why did you define the  function to be `virtual` in the first place?_ Most reasonable answers to that question encountered to date have been along the lines: This is a fundamental function in a framework that the framework builders needed to override but isn’t safe for general users to override. Be suspicious towards such claims and be sure `final` is really appropriate.

If it is performance (inlining) you want or you simply never want to  override, it is typically better not to define a function to be `virtual` in the first place. **This is not Java!**

`final` is only a contextual keyword, so you can still use it as an identifier:

```cpp
int final = 7;  // not recommended
```



### Explicit conversion operators 

C++98 provides implicit and `explicit` constructors; that is, the conversion defined by a constructor declared `explicit` can be used only for explicit conversions whereas other constructors can be used for implicit conversions also. For example:

```cpp
struct S { S(int); };   // "ordinary constructor" defines implicit conversion
S s1(1);        // ok
S s2 = 1;   		// ok
void f(S);
f(1);       // ok (but that's often a bad surprise -- what if S was vector?)

struct E { explicit E(int); };  // explicit constructor
E e1(1);        // ok
E e2 = 1;   // error (but that's often a surprise)
void f(E);
f(1);       // error (protects against surprises -- e.g. std::vector's constructor from int is explicit)
```

However, a constructor is not the only mechanism for defining a  conversion. If we can’t modify a class, we can define a conversion  operator from a different class. For example:

```cpp
struct S { S(int) { } /* ... */ };
struct SS {
  int m;
  SS(int x) :m(x) { }
  operator S() { return S(m); }  // because S don't have S(SS); non-intrusive
};

SS ss(1);
S s1 = ss;  // ok; like an implicit constructor
S s2(ss);   // ok ; like an implicit constructor
void f(S);
f(ss);      // ok; like an implicit constructor
```

Unfortunately, C++98 had no `explicit` conversion  operators, largely because there are far fewer problematic examples.  C++11 deals with that oversight by allowing conversion operators to be `explicit`. For example:

```cpp
struct S { S(int) { } };
struct SS {
  int m;
  SS(int x) :m(x) { }
  explicit operator S() { return S(m); }  // because S don't have S(SS)
};

SS ss(1);
S s1 = ss;  // error; like an explicit constructor
S s2(ss);   // ok ; like an explicit constructor
void f(S);
f(ss);      // error; like an explicit constructor
```



## Other Types

### enum class 

The `enum class`es ("new `enum`s", "strong `enum`s") address three problems with traditional C++ enumerations:

- Conventional `enum`s implicitly convert to an integer, causing errors when someone does not want an enumeration to act as an integer. 
- Conventional `enum`s export their enumerators to the surrounding scope, causing name clashes. 
- The underlying type of an `enum` cannot be specified, causing confusion, compatibility problems, and makes forward declaration impossible. 

`enum class`es ("strong `enum`s") are strongly typed and scoped:

```cpp
enum Alert { green, yellow, orange, red }; // traditional enum
enum class Color { red, blue };   // scoped and strongly typed enum
																	// no export of enumerator names into enclosing scope     
																	// no implicit conversion to int
enum class TrafficLight { red, yellow, green };
Alert a = 7;              // error (as ever in C++)
Color c = 7;              // error: no int->Color conversion
int a2 = red;             // ok: Alert->int conversion
int a3 = Alert::red;      // error in C++98; ok in C++11
int a4 = blue;            // error: blue not in scope
int a5 = Color::blue;     // error: not Color->int conversion
Color a6 = Color::blue;   // ok
```

As shown, traditional `enum`s work as usual, but you can now optionally qualify enumerators with the `enum` name

The new `enum`s are "`enum class`" because they combine aspects of traditional enumerations (names values) with aspects of classes (scoped members and absence of conversions). This is the same name for this feature as when it was originally designed in [C++/CLI](http://www.ecma-international.org/publications/standards/Ecma-372.htm) before being proposed for ISO C++.

Being able to specify the underlying type allows simpler interoperability and guaranteed sizes of enumerations:

```cpp
enum class Color : char { red, blue };  // compact representation
enum class TrafficLight { red, yellow, green };  // by default, the underlying type is int
enum E { E1 = 1, E2 = 2, Ebig = 0xFFFFFFF0U };   // how big is an E?
											// (whatever the old rules say;
											// i.e. "implementation defined")
enum EE : unsigned long { EE1 = 1, EE2 = 2, EEbig = 0xFFFFFFF0U };   // now we can be specific
```

It also enables forward declaration of enums:

```cpp
enum class Color_code : char;     // (forward) declaration
void foobar(Color_code* p);       // use of forward declaration
// ...
enum class Color_code : char { red, yellow, green, blue }; // definition
```

The underlying type must be one of the signed or unsigned integer types; the default is `int`.

In the standard library, enum classes are used

- For mapping systems specific error codes: In : `enum class errc;` 
- For pointer safety indicators: In : `enum class pointer_safety { relaxed, preferred, strict };` 
- For I/O stream errors: In : `enum class io_errc { stream = 1 };` 
- For asynchronous communications error handling: In : `enum class  future_errc { broken_promise, future_already_retrieved,  promise_already_satisfied };` 

Several of these have operators such as `==` defined.



## Templates

## Concurrency

## Miscellaneous Language Features

## General Libraries

## Containers and Algorithms

## Library Concurrency



## References

- [C++11 Language Extensions — General Features](https://isocpp.org/wiki/faq/cpp11-language)
- [C++11 Language Extensions — Miscellaneous Language Features](https://isocpp.org/wiki/faq/cpp11-language-misc)
- 
