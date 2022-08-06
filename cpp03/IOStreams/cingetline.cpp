//streams.cpp
#include <iostream>
using namespace std;

void testInputWithGetline();
void printStreamState();

int main()
{
    printStreamState();

    cout << "Let's test getline now\n" << endl;
    testInputWithGetline();

    if( ! cin.good() )
    {
        cerr << "\nsomething isn't right!" << endl;
        cin.clear();
        printStreamState();
    }

    cout << endl;

    return 0;
}

void testInputWithGetline()
{
    const int SIZE = 80;
    char buffer[ SIZE ]; // create array of 80 characters
    // input characters in buffer via cin function getline
    cout << "Enter a sentence:" << endl;
    cin.getline( buffer, SIZE );
    // display buffer contents
    cout << "\nThe sentence entered is:" << endl << buffer << endl;
}

void printStreamState()
{
    cout << "cin.rdstate(): " << cin.rdstate() << endl;
    cout << "cin.eof():     " << cin.eof() << endl;
    cout << "cin.fail():    " << cin.fail() << endl;
    cout << "cin.bad():     " << cin.bad() << endl;
    cout << "cin.good():    " << cin.good() << endl << endl;
}
