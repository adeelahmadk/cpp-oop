// inputs.cpp
#include <iostream>
#include <limits>
#include "inputs.h"

static void SafeInput::ignoreLine()
{
    std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
}

static int SafeInput::getInteger( const string &prompt )
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
}

static float SafeInput::getFloat( const string &prompt )
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
}

static string SafeInput::getString( const string &prompt )
{
    while( true ) // Loop until user enters a valid input
    {
        std::cout << prompt;
        char str[NAME_LENGTH];
        std::cin.getline( str, NAME_LENGTH );

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
            /* ignoreLine(); // remove any extraneous input */
            return string(str);
        }
    }
}
