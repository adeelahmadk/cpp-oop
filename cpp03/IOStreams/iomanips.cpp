// test stream manipulators
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void printJustified( int );
void printPadded( int, unsigned int = 10 );
void printDecimalNumbers( double, unsigned int = 5 );

int main()
{
    int x = 12345;
    double y = 1.2345e-10;

    // use cout flags function to save original format
    ios_base::fmtflags originalFormat = cout.flags();

    cout << "Print an integer left, right and internal aligned:\n";
    printJustified( x );
    cout << endl;
    x = 10;
    cout << "Print an integer in padded tabular form:\n";
    printPadded( x );
    cout << endl;
    cout << "Print a floating-point number in fixed and scientific forms:\n";
    printDecimalNumbers( y );
    cout << endl;

    cout.flags( originalFormat ); // restore format

    return 0;
}

void printJustified( int x )
{
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
        << internal << showpos << setw( 10 ) << x << noshowpos << endl;
}

void printPadded( int value, unsigned int rows )
{
    // save the default fill character
    char savedFill = cout.fill();
    // print table header
    cout << setw(15) << left << "Number"
        << setw(15) << right << "Hex"
        << "  "
        << setw(15) << internal << "Square"
        << showbase << uppercase  // show base, hex digits in capital letters
        << endl;
    for( unsigned int count = 0; count < rows; count++ )
    {
        // print the integer left aligned
        cout << setw(15) << left << setfill(' ') << value
            // print the hex value right aligned with underscore as fill character
            << setw(15) << right << setfill('_') << hex << value << dec
            << "  "  // just keeping two columns apart
            // print the square of the number internal alignment
            // showing +ve signe with caret (^) as fill character
            << setw(15) << internal << showpos << setfill('^') << ( value * value )
            // restore +ve sign setting for
            // 1st column in next iteration
            << noshowpos << endl;
        // left shift the integer by 1 place
        // ( equals to value *= 2 )
        value <<= 1;
    }
    cout << noshowbase << nouppercase;
    // restore the default fill character
    cout.fill(savedFill);
}

void printDecimalNumbers( double value, unsigned int rows )
{
    // print table header
    cout << setw(15) << "Number"
        << setw(15) << "Sqrt Fixed"
        << setw(20) << "Sqrt Scientific"
        << endl;
    for( unsigned int count = 0; count < rows; count++ )
    {
        // calculate square root of the FP value
        double fpValue = sqrt( value );
        cout << setw(15) << value
            // print square root in fixed-point format and
            // precision of 8 decimal places
            << setw(15) << fixed << setprecision(8) << fpValue
            // print square root in scientific format and
            // precision of 8 decimal places => Sticky manipulator!
            << setw(20) << scientific << fpValue
            << endl;
        // change the FP number
        value *= 5;
    }

}
