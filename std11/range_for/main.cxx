#include <ios>
#include <iostream>
#include <iomanip>
#include <vector>
// #include <cmath>
using std::cout;
using std::endl;
using std::vector;

void print(const vector<double>& v)
{
  for (auto x : v) cout << x << ' ';
}

void double_it( vector<double>& v )
{
  for (auto& x : v)  // using a reference to allow us to change the value
    x *= 2;
}

int main (int argc, char *argv[])
{
  vector<double> v = { 1, 2, 3.456, 99.99 };

  cout << "vector's elements...\n";
  print(v);
  cout << endl;

  cout << "double all elements...\n";
  double_it(v);
  print(v);
  cout << endl;

  return 0;
}
