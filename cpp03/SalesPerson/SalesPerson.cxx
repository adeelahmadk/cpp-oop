// SalesPerson class member-function definitions.
#include <iostream>
#include <iomanip>
#include <cstring>
#include "SalesPerson.h" // include SalesPerson class definition

using namespace std;

// initialize elements of array sales to 0.0
SalesPerson::SalesPerson(const char * const fn, const char * const ln)
{
    strncpy(firstName, fn, nameLength - 1);
    strncpy(lastName, ln, nameLength - 1);
    for ( int i = 0; i < monthsPerYear; i++ )
        sales[ i ] = 0.0;
} // end SalesPerson constructor

// get 12 sales figures from the user at the keyboard
void SalesPerson::getSalesFromUser()
{
    double salesFigure;
    for ( int i = 1; i <= monthsPerYear; i++ )
    {
        cout << "Enter sales amount for month " << i << ": ";
        cin >> salesFigure;
        setSales( i, salesFigure );
    } // end for
} // end function getSalesFromUser

// set one of the 12 monthly sales figures; function subtracts
// one from month value for proper subscript in sales array
void SalesPerson::setSales( int month, double amount )
{
    // test for valid month and amount values
    if ( month >= 1 && month <= monthsPerYear && amount > 0 )
        sales[ month - 1 ] = amount; // adjust for subscripts 0-11
    else // invalid month or amount value
        cout << "Invalid month or sales figure" << endl;
} // end function setSales

// print total annual sales (with the help of utility function)
void SalesPerson::printAnnualSales()
{
    cout << "\n" << lastName << ", " << firstName << ":" << endl
        << setprecision( 2 ) << fixed
        << "The total annual sales are: $"
        << totalAnnualSales() << endl; // call utility function
} // end function printAnnualSales

// private utility function to total annual sales
double SalesPerson::totalAnnualSales()
{
    double total = 0.0; // initialize total
    for ( int i = 0; i < monthsPerYear; i++ ) // summarize sales results
        total += sales[ i ]; // add month i sales to total
    return total;
} // end function totalAnnualSales
