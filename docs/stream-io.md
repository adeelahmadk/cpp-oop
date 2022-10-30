# Stream I/O



[Introduction](#Introduction)

1. [Stream Output](#Stream-Output)
2. [Stream Input](#Stream-Input)
    1. [`cin` and strings](#cin-and-strings)
    2. [Stream Management Functions](#Stream-Management-Functions)
3. [Unformatted I/O](#Unformatted-I/O)
4. [Stream Manipulators](#Stream-Manipulators)
5. [Stream Error States](#Stream-Error-States)
6. [`std::cin` and handling invalid input](#std-cin-and-handling-invalid-input)



## Introduction

C++ I/O occurs in **streams**, which are sequences of bytes. In input operations, the bytes flow from a **device** (e.g., a keyboard, a disk drive, a network connection, etc.) to **main memory**. In output operations, bytes flow from main memory to a device (e.g., a display screen, a printer, a disk drive, a network connection, etc.). An application may associate any meaning or abstraction with these bytes. The bytes could represent characters, raw data, graphics images, digital speech, digital video or any other information that has some meaning for an application. The system I/O mechanisms should transfer bytes from devices to memory (and vice versa) *consistently* and *reliably*. The time these transfers take, depending on the nature of the target device (e.g. mechanical disk, tape drive, printer etc.), can be much greater than the time the processor requires to manipulate data internally. Thus, I/O operations require careful planning and tuning to ensure optimal performance. C++ provides both “low-level” (i.e., unformatted I/O) and “high-level” (i.e., formatted I/O) I/O capabilities. 

- **Low-level I/O** capabilities specify that:
    - some number of bytes should be transferred device-to-memory or memory-to-device.
    - the individual byte is the item of interest.
    - provide high-speed, high-volume transfers
    - but are not particularly convenient for programs with higher level of abstraction. 
- **Higher-level I/O** capabilities:
    - formatted I/O, in which bytes are grouped into meaningful units (integers, floating-point numbers, characters, strings and user-defined types).
    - type-oriented capabilities are satisfactory for most I/O other than high-volume file processing.
    - programmers generally prefer to deal with a higher-level view of data

In the past, the C++ classic stream libraries enabled input and output of `chars`. Because a `char` normally occupies one byte, it can represent only a limited set of characters (such as those in the ASCII character set). However, many languages use alphabets that contain more characters than a single-byte char can represent. The ASCII character set does not provide these characters; the **Unicode® character set** does. Unicode is an extensive international character set that represents the majority of the world’s “*commercially viable*” languages, mathematical symbols and much more. For more information on Unicode, visit [www.unicode.org](www.unicode.org).

C++ includes the **standard stream libraries**, which enable developers to build systems capable of performing I/O operations with Unicode characters. For this purpose, C++ includes an additional character type called `wchar_t`, which can store 2-byte Unicode characters. The C++ standard also redesigned the classic C++ stream classes, which processed only chars, as class templates with separate **specializations** for processing characters of types `char` and `wchar_t`, respectively.

The `<iostream>` header file defines the `cin`, `cout`, `cerr` and `clog` objects, which correspond to the standard input stream, the standard output stream, the unbuffered standard error stream and the buffered standard error stream, respectively. Both unformatted and formatted-I/O services are provided.

| Stream Object | description                                 |
| :------------ | :------------------------------------------ |
| `cin`         | standard input stream                       |
| `cout`        | standard output stream                      |
| `cerr`        | standard error (output) stream (unbuffered) |
| `clog`        | standard logging (output) stream (buffered) |

The iostream library provides many templates for handling common I/O operations. Each template has a predefined template specialization that enables char I/O. In addition, the `iostream` library provides a set of typedefs that provide aliases for these template specializations. The typedef specifier declares synonyms (aliases) for previously defined data types. For example, 

| Class Template   | `typedef` Specialization | Description                                        |
| ---------------- | ------------------------ | -------------------------------------------------- |
| `basic_istream`  | `istream`                | specialized `char`  stream-input                   |
| `basic_ostream`  | `ostream`                | specialized `char`  stream-output                  |
| `basic_iostream` | `iostream`               | specialized `char`  stream-input and stream-output |



### Stream Output

C++ determines data types automatically—an improvement over C. This feature sometimes “gets in the way.” For example, suppose we want to print the address stored in a `char *` pointer. The `<<` operator has been overloaded to output a `char *` as a null-terminated string. To output the address, you can cast the `char *` to a `void *` (this can be done to any pointer variable).

```c++
const char *const word = "again";
// display value of char *, then display value of char *
// static_cast to void *
cout << "Value of word is: " << word << endl
<< "Value of static_cast< void * >( word ) is: "
<< static_cast< void * >( word ) << endl;
```



We can use the `put` member function to output characters. For example, the statement

```c++
cout.put( 'C' ).put( 'A' ).put( 'T' ).put( '\n' );
```

displays CAT a single character at a time followed by a newline character. These are called **cascaded function calls** which are made possible by the `ostream` reference returned by the `put` function. The put function also may be called with a numeric expression that represents an ASCII value, as in the following statement

```c++
cout.put( 65 );
```

which outputs A .

### Stream Input

[ref^](https://en.cppreference.com/w/cpp/io/basic_istream)

C++ `iostream` library provides standard stream input object `cin` where the standard input by default is the keyboard. For formatted input operations, `cin` is used together with the extraction operator (`>>`) then followed by the variable where the extracted data is stored. In this case, note that the characters introduced using the keyboard are only transmitted to the program when the `ENTER` (or `RETURN`) key is pressed.

```c++
int age;
cin >> age;
```

The extraction operation on `cin` uses the type of the variable after the `>>` operator to determine how it interprets the characters read from the input; if it is an integer, the format expected is a series of digits, if a string a sequence of characters, etc. Pretty simple, right? What happens in the example above if the user enters something else that cannot be interpreted as an integer? Well, in this case, the extraction operation fails. And this, by default, lets the program continue without setting a value for variable, producing undetermined results if the value of the variable is used later.

This is very poor program behavior. Only very simple programs should rely on values extracted directly from `cin` without further checking. A little later we will see how *stringstreams* can be used to have better control over user input.

#### cin and strings

The extraction operator can be used on `cin` to get strings of characters. However, `cin` extraction always considers spaces (whitespaces, tabs, new-line...) as terminating the value being extracted, and thus extracting a string means to always extract a single word, not a phrase or an entire sentence.

`basic_istream` provides functions specialized to input characters and strings. Most common of these are `get` and `getline`.

Function `get` has multiple variations for different scenarios. For example,

| Function                                                     | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `int_type get();`                                            | inputs one character from the<br/>designated stream (including<br/>white-space characters and other<br/>non-graphic characters, such as the<br/>key sequence that represents end-of-file) |
| `basic_istream& get( char_type& ch );`                       | a character reference to read input                          |
| `basic_istream& get(`<br/>        `char_type* s,`<br/>        `std::streamsize count );` | a character array to read input and<br/>a size limit<br/>    |
| `basic_istream& get(`<br/>        `char_type* s,`<br/>        `std::streamsize count`<br/>        `char_type delim );` | a character array to read input and<br/>a size limit<br/>a character delimiter (with default value '\n' ) |

The fourth version of `get` takes three arguments—a character array, a size limit and a delimiter (with default value `'\n'` ). This version reads characters from the input stream. It either reads one fewer than the specified maximum number of characters and terminates or terminates as soon as the *delimiter* is read. A **null character is inserted to terminate the input string** in the character array used as a buffer by the program. The **delimiter is not placed in the character array but does remain in the input stream** (the delimiter will be the next character read). **Thus, the result of a second consecutive get is an empty line**, unless the delimiter character is removed from the input stream (possibly with `cin.ignore()` ).

As a function with no arguments:

```c++
int character; // use int, because char cannot represent EOF

// use get to read each character; use put to display it
while ( ( character = cin.get() ) != EOF )
	cout.put( character );
```

As a function with three arguments and last one optional:

```c++
// create a char array with 80 elements
const int SIZE = 80;
char buffer1[ SIZE ];
char buffer2[ SIZE ];

// use cin.get to input characters into buffer
cin.get( buffer1, SIZE );
// or change the delimiter if needed
cin.get( buffer2, SIZE, '|' );
```

Member function `getline` operates similarly to the third version of the get member function and inserts a null character after the line in the character array. The `getline` function **removes the delimiter from the stream** (i.e., reads the character and discards it), but **does not store it in the character array**.

Looking at the available variations of the function `getline`:

| Function                                                     | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `basic_istream& getline(`<br/>        `char_type* s,`<br/>        `std::streamsize count );` | a character array to read input and<br/>a size limit<br/>    |
| `basic_istream& getline(`<br/>        `char_type* s,`<br/>        `std::streamsize count,`<br/>        `char_type delim );` | a character array to read input and<br/>a size limit<br/>a character delimiter (with default value '\n' ) |

For example

```c++
const int SIZE = 80;
char buffer[ SIZE ]; // create array of 80 characters
// input characters in buffer via cin function getline
cout << "Enter a sentence:" << endl;
cin.getline( buffer, SIZE );
```

#### Stream Management Functions

`istream` provides function to manage the input stream.

| Function  | Description                                                  |
| --------- | ------------------------------------------------------------ |
| `ignore`  | Extracts and discards characters from the input stream until and including `delim`. |
| `putback` | Puts a character `ch` back to the input stream so the next extracted character will be `ch`. |
| `peek`    | reads the next character in input stream without extracting it |



### Unformatted I/O

Unformatted input/output is performed using the `read` and `write` member functions of `istream` and `ostream` , respectively. Member function read input bytes to a character array in memory; member function write outputs bytes from a character array. These bytes are not formatted in any way. The `write` function outputs the designated number of characters from a buffer (including null characters). The `read` member function inputs a designated number of characters into a character array. If fewer than the designated number of characters are read, `failbit` (discussed later) is set. Member function `gcount` reports the number of characters read by the last input operation. As an example:

```c++
const int SIZE = 80;
char buffer[ SIZE ]; // create array of 80 characters

// use function read to input characters into buffer
cout << "Enter a sentence:" << endl;
cin.read( buffer, 20 );

// use functions write and gcount to display buffer characters
cout << endl << "The sentence entered was:" << endl;
cout.write( buffer, cin.gcount() );
cout << endl;
```



### Stream Manipulators

The `<iomanip>` header declares services useful for performing formatted I/O with socalled parameterized stream manipulators, such as `setw` and `setprecision`.

| Function       | Type                 | Description                                                  |
| -------------- | -------------------- | ------------------------------------------------------------ |
| `left`         | alignment            | Left justify output in a field. Padding characters appear to the right if necessary. |
| `right`        | alignment            | Right justify output in a field. Padding characters appear to the left if necessary. |
| `internal`     | alignment            | a number’s sign should be left justified in a field and a number’s magnitude should be right justified in that same field |
| `fill`         | alignment            | member function to set padding character                     |
| `setfill`      | alignment            | stream manipulator to set padding character                  |
| `width`        | field width          | member function to set field width to print a value          |
| `setw`         | field width          | stream manipulator to set field width to print a value       |
| `dec`          | integral, sticky^!^  | set the base to hexadecimal (base 16)                        |
| `oct`          | integral, sticky     | set the base to octal (base 8)                               |
| `hex`          | integral, sticky     | set the base to decimal (base 10)                            |
| `setbase`      | integral, sticky     | takes one integer argument of 10 , 8 , or 16 to set the base ^+^ |
| `showbase`     | integral             | the base of a number is to be output ahead of the number<br/>(a leading 0 for octals; a leading 0x or 0X for hex).<br/>resets with `noshowbase`. |
| `showpoint`    | fp precision, sticky | floating-point numbers should be output with a decimal<br/>point. resets with `noshowpoint`. |
| `precision`    | fp precision, sticky | stream manipulator to set floating-point precision,<br/>a call to `precision` with no argument returns the <br/>current precision setting. |
| `setprecision` | fp precision, sticky | member function to set floating-point precision              |
| `fixed`        | fp precision, sticky | output a floating-point value in fixed-point notation with <br/>a specific number of digits to the right of the decimal point. |
| `scientific`   | fp precision, sticky | output a floating-point value in scientific notation.        |
| `uppercase`    | numeric, sticky      | uppercase letters (i.e., X and A through F ) should be <br/>used in a hexadecimal integer and that uppercase E <br/>should be used when representing a floating-point value <br/>in scientific notation. resets with `nouppercase` |
| `showpos`      | numeric, sticky      | positive numbers should be preceded by a plus sign (+).<br/>This setting is reset with stream manipulator `noshowpos` . |
| `boolalpha`    | boolean, sticky      | boolean values should be printed as alphabetic aliases (true / false). reset with `noboolaplha` |

( **!** ) sticky means the value remains the same until changed explicitly.

( **+** ) Using `setbase` (or any other parameterized manipulator) requires the inclusion of the `<iomanip>` header file.

#### Integral base manipulators

```c++
// use hex stream manipulator to show hexadecimal number
int number = 42;

// use oct stream manipulator to show octal number
cout << "number: " << dec << number
  	<< "\nin octal is: " << oct << number << endl;

// use setbase stream manipulator to show decimal number
cout << "\nin hex is: " << hex << number
		<< setbase( 10 )
  	<< " in decimal is: " << number << endl;
```

#### Floating-point precision

```c++
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
  double root2 = sqrt( 2.0 ); // calculate square root of 2
  int places; // precision, vary from 0-9
  int savedPrecision = cout.precision(); // save existing value
  
  cout << "Square root of 2 with precisions 0-9." << endl
  	<< "Precision set by ios_base member function "
    << "precision:" << endl;
  cout << fixed; // use fixed-point notation
  // display square root using ios_base function precision
  for ( places = 0; places <= 9; places++ )
  {
    cout.precision( places );
    cout << root2 << endl;
  } // end for
  
  cout << "\nPrecision set by stream manipulator "
  	<< "setprecision:" << endl;
  // set precision for each digit, then display square root
  for ( places = 0; places <= 9; places++ )
  	cout << setprecision( places ) << root2 << endl;
  
  cout.precision(savedPrecision); // resotre the original value
  return 0;
} // end main
```

#### Decimal Point

```c++
// display double values with default stream format
cout << "Before using showpoint" << endl
<< "9.9900 prints as: " << 9.9900 << endl
<< "9.9000 prints as: " << 9.9000 << endl
<< "9.0000 prints as: " << 9.0000 << endl << endl;

// display double value after
cout << showpoint
<< "After using showpoint" << endl
<< "9.9900 prints as: " << 9.9900 << endl
<< "9.9000 prints as: " << 9.9000 << endl
<< "9.0000 prints as: " << 9.0000 << endl;
```

#### Justification

```c++
int x = 12345;
// display x right justified (default)
cout << "Default is right justified:" << endl
	<< setw( 10 ) << x;
// use left manipulator to display x left justified
cout << "\n\nUse std::left to left justify x:\n"
	<< left << setw( 10 ) << x;
// use right manipulator to display x right justified
cout << "\n\nUse std::right to right justify x:\n"
	<< right << setw( 10 ) << x << endl;
// display value with internal spacing and plus sign
cout << "\n\nUse std::internal to right justify x with std::showpos:\n"
  << internal << showpos << setw( 10 ) << x << endl;
```

#### Padding, Justification, Alignment, Uppercase, 

```c++
int x = 10, rows = 10;
// display x
cout << x 
  << " printed as int, left justified, default pad character (space)\n"
  << "and as hex, uppercase, right justified, _ pad character\n"
  << "and squared as dec, internal justified, ^ pad character, "
  << "with + sign\n:"
  << endl;

// print table header
cout << setw(15) << left << "Number"
  << setw(15) << right << "Hex"
  << "  "
  << setw(15) << internal << "Square"
  << showbase // display with base
  << uppercase // display hex digits in uppercase
  << endl;
for( unsigned int count = 0; count < rows; count++ )
{
  // display with left justification
  cout << setw(15) << left << setfill(' ') << x
    // display using padded characters '_', right justified
    << setw(15) << right << setfill('_') << hex << x
    << dec << "  "
    // display as hex using '^' padded characters, internal justified
    // and show positive (+) sign
    << setw(15) << internal << showpos << setfill('^') << ( x * x )
    // restore positive sign setting for next iteration
    << noshowpos << endl;
  // left shift value by 1 (= value * 2)
  x = x << 1;
}

```

#### Floating-Point, Fixed, Scientific Notation

```c++
unsigned int rows = 5;
double x = 1.2345e-10;
// print table header
cout << setw(15) << "Number"
  << setw(15) << "Sqrt Fixed"
  << setw(20) << "Sqrt Scientific"
  << setprecision(8) // set precision for floating point values
  << endl;
for( unsigned int count = 0; count < rows; count++ )
{
  double fpValue = sqrt( x );
  // 
  cout << setw(15) << x
    // display in fixed-point notation
    << setw(15) << fixed << fpValue
    // display in scientific notation
    << setw(20) << scientific << fpValue
    << endl;
  x *= 5;
}

```

#### Boolean Format

```c++
bool booleanValue = true;
// display default true booleanValue
cout << "booleanValue is " << booleanValue << endl;
// display booleanValue after using boolalpha
cout << "booleanValue (after using boolalpha) is "
	<< boolalpha << booleanValue << endl << endl;

cout << "switch booleanValue and use noboolalpha" << endl;

booleanValue = false; // change booleanValue
cout << noboolalpha << endl; // use noboolalpha
// display default false booleanValue after using noboolalpha
cout << "booleanValue is " << booleanValue << endl;
// display booleanValue after using boolalpha again
cout << "booleanValue (after using boolalpha) is "
	<< boolalpha << booleanValue << endl;
```

#### Setting and Resetting the Format State

```c++
// use cout flags function to save original format
ios_base::fmtflags originalFormat = cout.flags();

cout << showbase << oct << scientific; // change format
// display flags value, int and double values (new format)
cout << "The value of the flags variable is: " << cout.flags()
<< "\nPrint int and double in a new format:\n"
<< integerValue << '\t' << doubleValue << endl;

cout.flags( originalFormat ); // restore format
```



### Stream Error States



| Function  | Description                                                  |
| --------- | ------------------------------------------------------------ |
| `good`    | checks if no error has occurred i.e. I/O operations are available |
| `eof`     | checks if end-of-file has been reached                       |
| `fail`    | checks if an error has occurred                              |
| `bad`     | checks if a non-recoverable error has occurred               |
| `rdstate` | returns state flags                                          |
| `clear`   | modifies state flags                                         |

`rdstate` returns current stream error state. It is a bitmask type and can be a combination of the following constants (defined as `static const` in `ios::ios_base::`):

| Constant  | Explanation                                                  |
| --------- | ------------------------------------------------------------ |
| `goodbit` | no error                                                     |
| `badbit`  | irrecoverable stream error                                   |
| `failbit` | input/output operation failed (formatting or extraction error) |
| `eofbit`  | associated input sequence has reached end-of-file            |

#### Examples

```c++
#include <iostream>
#include <sstream>
#include <limits>
 
int main()
{
    std::istringstream input("1\n"
                             "some non-numeric input\n"
                             "2\n");
    for(;;) {
        int n;
        input >> n;
 
        if ( input.eof() || input.bad() )
        {
            break;
        }
      	else if ( input.fail() )
        {
            input.clear(); // unset failbit
          	// skip bad input to the max possible stream size
            input.ignore(
              std::numeric_limits<std::streamsize>::max(),
              '\n' );
        } 
      	else
        {
            std::cout << n << '\n';
        }
    }
}
```



### std cin and handling invalid input

Programs with user interfaces requiring some form of input use `std::cin` to prompt the user. However, the C++ input library is so unrestricted that a user intentionally or unintentionally may enter anything. As a result, the programmers writing the application must consider how a user may **misuse** their program. A well written program that anticipates such misuse and handles these error conditions gracefully is said to be **robust**. 

> *robustness* is the ability of a *computer* system to cope with errors during execution and cope with erroneous input.
>
> – [*Robustness* (computer science)](https://en.wikipedia.org/wiki/Robustness_(computer_science))

When we use `operator>>` to get user input and put it into a  variable, this is called an “extraction”. The `>>` operator is accordingly called the extraction operator when used in this context.

When the user enters input in response to an extraction operation, that data is placed in a buffer inside of `std::cin`. A **buffer** (also called a data buffer) is simply a piece of memory set aside for  storing data temporarily while it’s moved from one place to another. In  this case, the buffer is used to hold user input while it’s waiting to  be extracted to variables.

When the extraction operator is used, the following procedure happens:

- If there is data already in the input buffer, that data is used for extraction.
- If the input buffer contains no data, the user is asked to input data for  extraction (this is the case most of the time). When the user hits  enter, a ‘`\n`’ character will be placed in the input buffer.
- `operator>>` extracts as much data from the input buffer as it can into the variable (ignoring any leading whitespace characters, such as spaces, tabs, or  ‘`\n`’).
- Any data that can not be extracted is left in the input buffer for the next extraction.

Extraction succeeds if at least one character is extracted from the  input buffer. Any unextracted input is left in the input buffer for  future extractions. For example:

```cpp
int x;
std::cin >> x;
# 5a
# x = 5
```

If the user enters “`5a`”, `5` will be extracted, converted to an integer, and assigned to variable `x`. “`a\n`” will be left in the input buffer for the next extraction.

Extraction fails if the input data does not match the type of the variable being extracted to. For example:

```cpp
int x;
std::cin >> x;
# b
# failbit is set
```

If the user were to enter ‘`b`’, extraction would fail because ‘b’ can not be extracted to an integer variable.

#### Validating input

The process of checking whether user input conforms to what the program is expecting is called **input validation**. There are three basic ways to do input validation:

- Inline (as the user types)
    - Prevent the user from typing invalid input in the first place.
- Post-entry (after the user types)
    - Let the user enter whatever they want into a string, then validate whether  the string is correct, and if so, convert the string to the final  variable format.
    - Let the user enter whatever they want, let `std::cin` and `operator>>` try to extract it, and handle the error cases.

The first style requires a synchronous character by character input (without being echoed to the screen) and printing only the validated characters. Unfortunately, `std::cin` doesn't support this style of validation.

Since strings do not have any restrictions on what characters can be  entered, extraction is guaranteed to succeed (though remember that  `std::cin` stops extracting at the first non-leading whitespace  character). Once a string is entered, the program can then parse the string to see if it is valid or not. Most often, we let `std::cin` and the extraction operator do the hard work. Under this method, we let the user enter whatever they want, have `std::cin` and `operator>>` try to extract it, and deal with the **fallout** if it fails.

##### A sample program

Consider the following calculator program without any error handling:

```cpp
#include <iostream>
using namespace std;

double getDouble()
{
    cout << "Enter a double value: ";
    double x;
    cin >> x;
    return x;
}

char getOperator()
{
    cout << "Enter one of the following: +, -, *, or /: ";
    char op;
    cin >> op;
    return op;
}

void printResult(double x, char operation, double y)
{
    switch (operation)
    {
    case '+':
        std::cout << x << " + " << y << " is " << x + y << '\n';
        break;
    case '-':
        std::cout << x << " - " << y << " is " << x - y << '\n';
        break;
    case '*':
        std::cout << x << " * " << y << " is " << x * y << '\n';
        break;
    case '/':
        std::cout << x << " / " << y << " is " << x / y << '\n';
        break;
    }
}

int main()
{
    double x = getDouble();
    char operation = getOperator();
    double y = getDouble();

    printResult(x, operation, y);

    return 0;
}
```

##### Types of invalid text input

We can generally separate input text errors into four types:

- Input extraction succeeds but the input is *meaningless to the program* (e.g. entering ‘k’ as your mathematical operator).
- Input extraction succeeds but the user enters *additional input* (e.g. entering ‘*q hello’ as your mathematical operator).
- Input *extraction fails* (e.g. trying to enter ‘q’ into a numeric input).
- Input extraction succeeds but the user *overflows a numeric value*.

Thus, to make our programs **robust**, whenever we ask the user for input, we ideally should determine whether each of the above can possibly occur,  and if so, write code to handle those cases.

##### Error case 1: Extraction succeeds but input is meaningless

This is the simplest case. Consider the following execution of the above program:

```
Enter a double value: 5
Enter one of the following: +, -, *, or /: k
Enter a double value: 7
```

The solution here is simple: do input validation. This usually consists of 3 steps:

1. Check whether the user’s input was what you were expecting.
2. If so, return the value to the caller.
3. If not, tell the user something went wrong and have them try again.

Here’s an updated `getOperator()` function that does input validation.

```cpp
char getOperator()
{
    while (true) // Loop until user enters a valid input
    {
        cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        cin >> operation;

        // Check whether the user entered meaningful input
        switch (operation)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation; // return it to the caller
        default: // otherwise tell the user what went wrong
            cerr << "Oops, that input is invalid. Please try again.\n";
        }
    } // and try again
}
```

Here we’re using a while loop to continuously loop until the user provides valid input.

##### Error case 2: Extraction succeeds but with extraneous input

Consider the following execution of the above program:

```
Enter a double value: 5*7
```

What do you think happens next?

```
Enter a double value: 5*7
Enter one of the following: +, -, *, or /: Enter a double value: 5 * 7 is 35
```

The program prints the right answer, but the formatting is all messed up.

When the user enters “`5*7`” as input, it goes into the buffer. Then `operator>>` extracts the `5` to variable `x`, leaving “`*7\n`” in  the buffer. Next, the program prints “`Enter one of the following: +, -,  *, or /:`”. However, when the extraction operator was called, it sees  “`*7\n`” waiting in the buffer to be extracted, so it uses that instead of asking the user for more input. Consequently, it extracts the ‘`*`’  character, leaving “`7\n`” in the buffer.

After asking the user to  enter another double value, the “`7`” in the buffer gets extracted without asking the user. Since the user never had an opportunity to enter additional data and hit enter (causing a newline), the output prompts all run together on the same line.

Although the above program works, the execution is messy. It would be better if any extraneous characters entered were simply ignored.  Fortunately, it’s easy to ignore characters:

```cpp
std::cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n' character is removed
```

This call would remove up to 100 characters, but if the user entered  more than 100 characters we’ll get messy output again. To ignore all  characters up to the next ‘\n’, we can pass `std::numeric_limits<std::streamsize>::max()` to `std::cin.ignore()`. `std::numeric_limits<std::streamsize>::max()` returns the largest value that can be stored in a variable of type `std::streamsize`. Passing this value to `std::cin.ignore()` causes it to disable the count check.

To ignore everything up to and including the next ‘\n’ character, we call

```cpp
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
```

Because this line is quite long for what it does, it’s handy to wrap it in a function which can be called in place of `std::cin.ignore()`.

```cpp
#include <limits> // for std::numeric_limits
using namespace std;

void ignoreLine()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
```

Since the last character the user entered must be a ‘`\n`’, we can tell `std::cin` to ignore buffered characters until it finds a newline  character (which is removed as well).

Let’s update our `getDouble()` function to ignore any extraneous input:

```cpp
double getDouble()
{
    cout << "Enter a double value: ";
    double x;
    cin >> x;
    ignoreLine();
    return x;
}
```

Now our program will work as expected, even if we enter “5*7” for the  first input -- the 5 will be extracted, and the rest of the characters  will be removed from the input buffer.

##### Error case 3: Extraction fails

Now consider the following execution of our updated calculator program:

```
Enter a double value: a
```

You shouldn’t be surprised that the program doesn’t perform as expected, but how it **fails** is interesting:

```
Enter a double value: a
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
```

and that last line keeps printing until the program is closed.

When the user enters ‘`a`’, that character is placed in the buffer. Then `operator>>` tries to extract ‘`a`’ to variable `x`, which is of type `double`. Since ‘`a`’ can’t be converted to a `double`, `operator>>` can’t do the extraction. Two things happen at this point: ‘`a`’ is left in the buffer, and `std::cin` goes into “failure mode”.

Once in “failure mode”, future requests for input extraction will  silently fail. Thus in our calculator program, the output prompts still print, but any requests for further extraction are ignored. This means that instead waiting for us to enter an operation, the input prompt is  skipped, and we get stuck in an infinite loop because there is no way to reach one of the valid cases.

Fortunately, we can detect whether an extraction has failed and fix it:

```cpp
if( cin.fail() ) // has a previous extraction failed?
{
    // yep, so let's handle the failure
    cin.clear(); // put us back in 'normal' operation mode
    ignoreLine(); // and remove the bad input
}

```

Because `std::cin` has a boolean conversion indicating whether the last input succeeded, it’s more idiomatic to write the above as following:

```cpp
if( ! cin ) // has a previous extraction failed?
{
    // yep, so let's handle the failure
    cin.clear(); // put us back in 'normal' operation mode
    ignoreLine(); // and remove the bad input
}

```

Let’s integrate that into our `getDouble()` function:

```cpp
double getDouble()
{
    while ( true ) // Loop until user enters a valid input
    {
        cout << "Enter a double value: ";
        double x;
        cin >> x;

        if( ! cin ) // has a previous extraction failed?
        {
            // yep, so let's handle the failure
            cin.clear(); // put us back in 'normal' operation mode
            ignoreLine(); // and remove the bad input
        }
        else // else our extraction succeeded
        {
            ignoreLine();
            return x; // so return the value we extracted
        }
    }
}
```

A failed extraction due to invalid input will cause the variable to be  zero-initialized. Zero initialization means the variable is set to `0`, `0.0`, `“”`, or whatever value 0 converts to for that type.

##### Error case 4: Extraction succeeds but the user overflows a numeric value

Consider the following simple example:

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    std::int16_t x{}; // x is 16 bits, holds from -32768 to 32767
    std::cout << "Enter a number between -32768 and 32767: ";
    std::cin >> x;

    std::int16_t y{}; // y is 16 bits, holds from -32768 to 32767
    std::cout << "Enter another number between -32768 and 32767: ";
    std::cin >> y;

    std::cout << "The sum is: " << x + y << '\n';
    return 0;
}
```

What happens if the user enters a number that is too large (e.g. 40000)?

```
Enter a number between -32768 and 32767: 40000
Enter another number between -32768 and 32767: The sum is: 32767
```

In the above case, `std::cin` goes immediately into “failure mode”, but  also assigns the closest in-range value to the variable. Consequently, `x` is left with the assigned value of `32767`. Additional inputs are skipped, leaving y with the initialized value of 0. We can handle this  kind of error in the same way as a failed extraction.

##### Putting it all together

Here’s our example calculator, updated with a few additional bits of error checking:

```cpp
#include <iostream>
#include <limits>

void ignoreLine()
{
    std::cin.ignore(
      std::numeric_limits<std::streamsize>::max(),
      '\n');
}

double getDouble()
{
    while( true ) // Loop until user enters a valid input
    {
        std::cout << "Enter a double value: ";
        double x;
        std::cin >> x;

        // Check for failed extraction
        if( ! std::cin ) // has a previous extraction failed?
        {
            // yep, so let's handle the failure
            std::cin.clear(); // put us back in 'normal' operation mode
            ignoreLine(); // and remove the bad input
            std::cerr << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            ignoreLine(); // remove any extraneous input
            return x;
        }
    }
}

char getOperator()
{
    while( true ) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation;
        std::cin >> operation;
        ignoreLine(); // // remove any extraneous input

        // Check whether the user entered meaningful input
        switch( operation )
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation; // return it to the caller
        default: // otherwise tell the user what went wrong
            std::cerr << "Oops, that input is invalid.  Please try again.\n";
        }
    } // and try again
}

void printResult( double x, char operation, double y )
{
    switch( operation )
    {
    case '+':
        std::cout << x << " + " << y << " is " << x + y << '\n';
        break;
    case '-':
        std::cout << x << " - " << y << " is " << x - y << '\n';
        break;
    case '*':
        std::cout << x << " * " << y << " is " << x * y << '\n';
        break;
    case '/':
        std::cout << x << " / " << y << " is " << x / y << '\n';
        break;
    default: // Being robust means handling unexpected parameters as well, even though getOperator() guarantees operation is valid in this particular program
        std::cerr << "Something went wrong: "
          << "printResult() got an invalid operator.\n";
    }
}

int main()
{
    double x = getDouble();
    char operation = getOperator();
    double y = getDouble();

    printResult( x, operation, y );

    return 0;
}
```



[^ Top](#Stream-IO)