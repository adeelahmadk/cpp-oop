// inputs.cpp
#include <iostream>
#include <limits>
#include "inputs.h"

// clear output buffer
void ignoreLine()
{
    std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
}

// ask user for an integer input
int getInteger( const string &prompt )
{
    while( true ) // Loop until user enters a valid input
    {
        std::cout << prompt;
        int x;
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
} // end function getInteger

// ask user for an float input
float getFloat( const string &prompt )
{
    while( true ) // Loop until user enters a valid input
    {
        std::cout << prompt;
        float x;
        std::cin >> x;

        // Check for failed extraction
        if( ! std::cin ) // has a previous extraction failed?
        {
            // yep, so let's handle the failure
            std::cin.clear(); // put us back in 'normal' operation mode
            ignoreLine(); // and remove the bad input
            std::cerr << "Oops, that input is invalid. Please try again.\n";
        }
        else
        {
            ignoreLine(); // remove any extraneous input
            return x;
        }
    }
} // end function getFloat

string getString( const string &prompt, const int length )
{
    while( true ) // Loop until user enters a valid input
    {
        std::cout << prompt;
        char str[length];
        std::cin.getline( str, length );

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
            return string(str);
        }
    }
} // end function getString

// get an answer in Yes or No from user
char askYesNo( const string &prompt )
{
    char request; // request from user

    // display request options
    cout << prompt << endl;
    do // input user request
    {
        cout << "(Y/N) ? ";
        request = getchar();
        ignoreLine();
    } while ( ( request != 'y' && request != 'Y' ) &&
            ( request != 'n' && request != 'N' ) );

    cout << endl;
    return request;
} // end function askYesNo
