#include <iostream>
using namespace std;

int main()
{
    // create two char arrays, each with 80 elements
    const int SIZE = 80;
    char buffer1[ SIZE ];
    char buffer2[ SIZE ];
    // use cin to input characters into buffer1
    cout << "Enter a sentence:" << endl;
    cin >> buffer1;
    // display buffer1 contents
    cout << "\nThe string read with cin was:" << endl
    << buffer1 << endl << endl;
    // use cin.get to input characters into buffer2
    cin.get( buffer2, SIZE );
    // display buffer2 contents
    cout << "The string read with cin.get was:" << endl
    << buffer2 << endl;
}
