# From C++98/03 to C++11

The purpose of this C++11 section is:

- To give a brief overview of the new facilities (language features and  standard libraries) offered by C++11 in addition to what is provided by  the previous version of the ISO C++ standard. 
- To give an idea of the aims of the ISO C++ standards effort. 
- To present a user’s view of the new facilities 
- To provide references to allow for a more in depth study of features. 

## What is C++11

C++11 is the ISO C++ standard formally ratified by a 21-0 national vote in August 2011. This [public working paper](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3337.pdf) is the January 2012 working draft, and contains the C++11 standard plus minor editorial changes.

C++11 is a major upgrade over C++98/03, with performance and convenience features that make it feel like a new language.

The differences between C++98 and C++03 are so few and so technical that they ought not concern users. This FAQ discusses changes between C++98/C++03 to C++11.

Before its official ratification in 2011, the then-under-development standard was unofficially called C++0x, as it was hoped to be completed in C++08 or C++09. Think of ‘x’ as hexadecimal (i.e., C++0B == C++11).

## Design Goals

In addition to the general design goals, to try to select rationally from the flood of suggestions the committee devised a set of specific design goals. The result has been a language with greatly improved abstraction mechanisms. When we say “abstraction” people often just think “classes” or “objects.” C++11 goes far beyond that: The range of user-defined types that can be cleanly and safely expressed has grown with the addition of features such as initializer-lists, uniform initialization, template aliases, rvalue references, defaulted and deleted functions, and variadic templates. 

The overall aims of the C++11 effort was to strengthen that:

- Make C++ a better language for systems programming and library building
- Make C++ easier to teach and learn
- Very stringent compatibility constraints

For more details see:

- B. Stroustrup: [What is C++11?](http://www.stroustrup.com/what-is-2009.pdf). CVu. Vol 21, Issues 4 and 5. 2009. 
- B. Stroustrup: [Evolving a language in and for the real world: C++ 1991-2006](http://www.stroustrup.com/hopl-almost-final.pdf). ACM HOPL-III. June 2007. 
- B. Stroustrup: [A History of C++: 1979-1991](http://www.stroustrup.com/hopl2.pdf). Proc ACM History of Programming Languages conference (HOPL-2). March 1993. 
- B. Stroustrup: [C and C++: Siblings](http://www.stroustrup.com/siblings_short.pdf). The C/C++ Users Journal. July 2002. 

## C++11 Standard Language Extensions

We have a [document](cpp11-lang-ext.md) that outlines the main language extensions introduced to the language in the C++11 standard. The list of topics covered in this document are:

1. [General Features](cpp11-lang-ext.md#General-Features)
2. [Classes](cpp11-lang-ext.md#Classes)
3. [Other Types](cpp11-lang-ext.md#Other-Types)
4. [Templates](cpp11-lang-ext.md#Templates)
5. [Concurrency](cpp11-lang-ext.md#Concurrency)
6. [Miscellaneous Language Features](cpp11-lang-ext.md#Miscellaneous-Language-Features)
7. [General Libraries](cpp11-lang-ext.md#General-Libraries)
8. [Containers and Algorithms](cpp11-lang-ext.md#Containers-and-Algorithms)
9. [Library Concurrency](cpp11-lang-ext.md#Library-Concurrency)



## Code Examples

Each example has been compiled and tested with `gcc` (version 9.4.0). Example directories contain a bash script to build and run. In case bash shell is not available, then examples can be compiled with the following command:

```shell
cd <example_directory>
# for gcc
g++ -std=c++11 -Wall -o type_deduct main.cxx
./type_deduct
# for clang
clang++ -std=c++11 -Wall -o type_deduct main.cxx
./type_deduct
# for mingw
g++.exe -std=c++11 -Wall -o type_deduct.exe main.cxx
.\type_deduct.exe
```

List of examples is as listed below:

| Example                      | Concept                                                      |
| ---------------------------- | ------------------------------------------------------------ |
| [type_deduct](./type_deduct) | `auto`: Type deduction                                       |
| [range_for](./range_for)     | Range-for statement                                          |
| [init_list](./init_list)     | List initialization, uniform initialization syntax & semantics |
| [rvalue_ref](./rvalue_ref)   | `rvalue` reference and move semantics                        |
|                              |                                                              |

## Where else can I read about C++11? 

The amount of information about C++11 is increasing as most C++  implementations provide the new language features and libraries. Here is a short list of sources:

- B. Stroustrup: [The C++ Programming Language (Fourth Edition)](http://www.stroustrup.com/4th.html). 
- B. Stroustrup: [A Tour of C++](http://www.stroustrup.com/Tour.html). 
- [The committe papers archive](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/). 
- The [C++11 standard (closest public approximation)](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3337.pdf)
- [The C++11 Wikipedia entry](http://en.wikipedia.org/wiki/C%2B%2B0x). This seems to be actively maintained, though apparently not by members of the committee. 
- [A list of support for C++11 features](http://wiki.apache.org/stdcxx/C%2B%2B0xCompilerSupport). 



## Videos about C++11

- B. Stroustrup, H. Sutter, H-J. Boehm, A. Alexandrescu, S.T.Lavavej,  Chandler Carruth, and Andrew Sutton: Several talks and panels from the [GoingNative 2012 conference](http://channel9.msdn.com/Events/GoingNative/GoingNative-2012). 
- B. Stroustrup, H. Sutter, S. Meyers, A. Alexandrescu, S.T.Lavavej,  Chandler Carruth, S. Parent, and M. Wong: Several talks and panels from  the [GoingNative 2013 conference](http://channel9.msdn.com/Events/GoingNative/2013).
- Herb Sutter: [Writing Modern C++ Code: How C++ has evolved over the years](http://channel9.msdn.com/Events/BUILD/BUILD2011/TOOL-835T). September 2011. 
- Herb Sutter: [Why C++?](http://channel9.msdn.com/posts/C-and-Beyond-2011-Herb-Sutter-Why-C). C++ and Beyond 2011, August 2011. 
- Herb Sutter: [(Not Your Father’s) C++](http://channel9.msdn.com/Events/Lang-NEXT/Lang-NEXT-2012/-Not-Your-Father-s-C-). Lang.NEXT, April 2012.
- Herb Sutter: [atomic<> Weapons: The C++ Memory Model and Modern Hardware, Part 1](http://channel9.msdn.com/Shows/Going+Deep/Cpp-and-Beyond-2012-Herb-Sutter-atomic-Weapons-1-of-2), [Part 2](http://channel9.msdn.com/Shows/Going+Deep/Cpp-and-Beyond-2012-Herb-Sutter-atomic-Weapons-2-of-2), [Slides](http://sdrv.ms/NxDB6u), from *C++ and Beyond*, August 2012.
- Lawrence Crowl: [Lawrence Crowl on C++ Threads](http://www-sop.inria.fr/geometrica/events/WG21_meeting_june_2008/public_talks.html). in Sophia Antipolis, June 2008. 
- Bjarne Stroustrup: [The design of C++0x](http://www.youtube.com/watch?v=lMmVuRNmHzQ). University of Waterloo, 2007. 
- Bjarne Stroustrup: [Initialization](http://video.google.com/videoplay?docid=5262479012306588324&ei=2eK7SaGiOILorgLo6p32CQ&q=C%2B%2B0x&hl=en). Google, 2007. 
- Bjarne Stroustrup: [C++0x – An overview](http://www-sop.inria.fr/geometrica/events/WG21_meeting_june_2008/public_talks.html). in Sophia Antipolis, June 2008. 
- Lawrence Crowl: [Threads](http://video.google.com/videoplay?docid=3528799355371049884&ei=NeS7SZLiCJGgqgKU_7GTCg&q=C%2B%2B0x&hl=en).
- Roger Orr: [C++0x](http://video.google.com/videoplay?docid=2165553273160626549&ei=geS7SaSyNYL8rgL7643TDQ&q=C%2B%2B0x&hl=en). January 2008. 
- Hans-J. Boehm: [Getting C++ Threads Right](http://www.youtube.com/watch?v=mrvAqvtWYb4). December 2007. 

