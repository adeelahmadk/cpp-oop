/**
* @file init_list/main.cxx
* @author Adeel Ahmad (6880680+adeelahmadk@users.noreply.github.com)
* @brief Example demonstrating c++11 uniform list initializations
* @version 0.1
* @date 2023-06-08
*
* @copyright Copyright (c) 2023
*
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using std::ostream;
using std::cout;
using std::endl;
using std::fixed;
using std::vector;

using matrix = vector<vector<double>>;  // rename a long complex type

class Point {
  friend ostream & operator<<(ostream &, const Point &);
public:
  float x_;
  float y_;
  Point(float a=0, float b=0) : x_(a), y_(b) {}
};

ostream & operator<<(ostream &out, const Point &p) {
  auto precision_value = cout.precision(2);
  cout << fixed
    << "Point(" << p.x_ << ", " << p.y_ << ")";
  cout.precision(precision_value);
  return out;
}

double euclidean_distance(Point &p1, Point &p2)
{
  return sqrt(pow(p1.x_ - p2.x_, 2) + pow(p1.y_ - p2.y_, 2));
}

void print_matrix(matrix&);

int main (int argc, char *argv[])
{
  vector<double> v { 1, 2, 3.456, 99.99 };    // direct list initialization
  int *int_list = new int[5] {1, 3, 5, 7, 9}; // copy list initialization

  matrix matA = {
    { 1, 2, 3 },
    { 4, 5, 6 },
    { 7, 8, 9 }
  };

  vector<Point> point_list {
    {3,1}, {5,4}, {-2, 7}, {-1, -2}
  };
  Point p1{1,2}, p2{5,4};

  auto ed = euclidean_distance(p1, p2);

  cout << "double vector:\n";
  for (auto x : v) {
    cout << x << " ";
  }
  cout << "\n" << endl;

  cout << "int array:\n";
  for (int i = 0; i < 5; ++i) {
    cout << int_list[i] << " ";
  }
  cout << "\n" << endl;

  auto precision_value = cout.precision(2);

  cout << "euclidean distance between "
  << p1 << " and " << p2 << " is " << ed << "\n" <<endl;

  cout << "List of points:\n";
  for (auto p : point_list)
    cout << p << " ";
  cout << "\n\n";

  cout << "Printing 2D vector:\n";
  print_matrix(matA);
  cout << endl;

  cout.precision(precision_value);

  delete []int_list;
  return 0;
}

void print_matrix(vector<vector<double>>& v)
{
  auto precision_value = cout.precision(2);
  cout << fixed;
  for (auto r : v) {
    for (auto x : r)
      cout << x << " ";
    cout << "\n";
  }
  cout.precision(precision_value);
}
