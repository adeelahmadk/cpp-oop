// Demonstrating the order in which constructors and
// destructors are called.
#include <iostream>
#include "CreateAndDestroy.h" // include CreateAndDestroy class definition

using namespace std;

void create( void ); // prototype

// passing a string literal instead of a char * raises compiler warning.
// Type casted a string literal to a char *
CreateAndDestroy first( 1, (char *)"(global before main)" ); // global object

int main()
{
    cout << "\nMAIN FUNCTION: EXECUTION BEGINS" << endl;

    CreateAndDestroy second( 2, (char *)"(local automatic in main)" );
    static CreateAndDestroy third( 3, (char *)"(local static in main)" );

    create(); // call function to create objects

    cout << "\nMAIN FUNCTION: EXECUTION RESUMES" << endl;
    CreateAndDestroy fourth( 4, (char *)"(local automatic in main)" );
    cout << "\nMAIN FUNCTION: EXECUTION ENDS" << endl;

    return 0;
} // end main
// function to create objects
void create( void )
{
    cout << "\nCREATE FUNCTION: EXECUTION BEGINS" << endl;

    CreateAndDestroy fifth( 5, (char *)"(local automatic in create)" );
    static CreateAndDestroy sixth( 6, (char *)"(local static in create)" );
    CreateAndDestroy seventh( 7, (char *)"(local automatic in create)" );

    cout << "\nCREATE FUNCTION: EXECUTION ENDS" << endl;
} // end function create
