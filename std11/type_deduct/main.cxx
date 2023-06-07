/**
* @file type_deduct/main.cxx
* @author Adeel Ahmad (6880680+adeelahmadk@users.noreply.github.com)
* @brief Example demonstrating type deduction with auto
* @version 0.1
* @date 2023-06-07
*
* @copyright Copyright (c) 2023
*
*/
#include <ios>
#include <iostream>
#include <iomanip>
#include <cmath>
using std::cout;
using std::endl;
using std::scientific;
using std::fixed;
using std::setprecision;

struct Point {
  int x, y;
  Point(int a=0, int b=0) : x(a), y(a) {}
};

double euclidean_squared(Point p1, Point p2)
{
  return (std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

int main (int argc, char *argv[])
{
  auto x = 42;         // int
  auto y = 3.5f;       // float
  auto z = sin(3.14);  // double
  Point p1{1,2}, p2{5,4};
  auto ed = euclidean_squared(p1, p2);

  cout << "x  [" << sizeof(x) << " bytes] : " << x << endl;
  cout << "y  [" << sizeof(y) << " bytes] : " << y << endl;
  cout << "z  [" << sizeof(z) << " bytes] : "
    << scientific << setprecision(5) << z << endl;
  cout << "ed [" << sizeof(z) << " bytes] : " 
    << fixed << setprecision(2) << ed << endl;

  return 0;
}
