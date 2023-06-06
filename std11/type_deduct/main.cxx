#include <ios>
#include <iostream>
#include <iomanip>
#include <cmath>
using std::cout;
using std::endl;
using std::scientific;
using std::setprecision;

int main (int argc, char *argv[])
{
  auto x = 42;         // int
  auto y = 3.5f;       // float
  auto z = sin(3.14);  // double

  cout << "x [" << sizeof(x) << " bytes] : " << x << endl;
  cout << "y [" << sizeof(y) << " bytes] : " << y << endl;
  cout << "z [" << sizeof(z) << " bytes] : "
    << scientific << setprecision(5) << z << endl;

  return 0;
}
