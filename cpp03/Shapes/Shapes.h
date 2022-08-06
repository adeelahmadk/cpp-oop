// Shapes.h
// Shape class hierarchy definition including:
//              Abstract Base Class (abc) 
//                       {Shape}
//                      /       \
//  {TwoDimensionalShape}     {ThreeDimensionalShape}  (sub-category abstract classes)
//              |                           |
//        --------------                 --------
//       /      |       \               /        \
//   Circle  Triangle  Rectangle     Sphere     Cube

#ifndef SHAPES_H
#define SHAPES_H

#include <string>
#include "Point.h"

using namespace std;

typedef struct {
    double x, y;
} Pair;

class Shape
{
public:
    Shape(); // constructor
    // pure virtual function
    virtual double getArea() const = 0;   // get area of the shape
    // pure virtual function
    virtual double getVolume() const = 0; // get volume of the shape
    virtual void print() = 0; // print shape information
    virtual ~Shape(); // destructor

    static const double PI;
protected:
    string name;
};

class TwoDimensionalShape : public Shape
{
public:
    TwoDimensionalShape(); // constructor
    // pure virtual function
    virtual double getArea() const = 0; // get area of the shape
    virtual double getVolume() const; // get volume of the shape
    virtual void print() = 0; // print shape information
    virtual ~TwoDimensionalShape(); // destructor
};

class ThreeDimensionalShape : public Shape
{
public:
    ThreeDimensionalShape(); // constructor
    // pure virtual function
    virtual double getArea() const; // get area of the shape
    virtual double getVolume() const = 0; // get volume of the shape
    virtual void print() = 0; // print shape information
    virtual ~ThreeDimensionalShape(); // destructor
};

class Circle : public TwoDimensionalShape
{
public:
    Circle( Point2D = Point2D(0,0), double = 1 ); // default constructor
    double getArea() const; // get area of the circle
    double getCircumference() const; // get circumference of the circle
    void print(); // print circle information
    ~Circle(); // destructor
private:
    Point2D center;
    double radius;
};

class Triangle : public TwoDimensionalShape
{
public:
    Triangle( Point2D, Point2D, Point2D ); // constructor
    double getArea() const; // get area of the triangle
    double getParimeter() const; // get parimeter of the triangle
    void print(); // print circle information
    ~Triangle(); // destructor
private:
    Point2D vA, vB, vC;   // vertices
    double eAB, eBC, eCA; // edge lengths
};

class Rectangle : public TwoDimensionalShape
{
public:
    Rectangle( Point2D, Point2D, Point2D, Point2D ); // constructor
    double getArea() const; // get area of the rectangle
    double getParimeter() const; // get parimeter of the rectangle
    void print(); // print rectangle information
    ~Rectangle(); // destructor
private:
    // verify vertices of rectangle
    bool isRectangle( Point2D &, Point2D &, Point2D &, Point2D & );
    Pair getMin( const Point2D [] ) const; // get min x in a list of vertices
    Pair getMax( const Point2D [] ) const; // get min x in a list of vertices
    Point2D vA, vB, vC, vD;
    double width, length;
};

/** leaving for later work and exercise
class Cube : public ThreeDimensionalShape
{
public:
    Cube( Point3D, double ); // constructor
    double getSurfaceArea() const; // get surface area of the cube
    double getVolume() const; // get volume of the cube
    void print(); // print cube information
    ~Cube(); // destructor
private:
    Point3D oVertex;
    double edgeLength;
};
*/

class Sphere : public ThreeDimensionalShape
{
public:
    Sphere( Point3D, double ); // constructor
    double getSurfaceArea() const; // get surface area of the sphere
    double getVolume() const; // get volume of the sphere
    void print(); // print circle information
    ~Sphere(); // destructor
private:
    Point3D center;
    double radius;
};

#endif
