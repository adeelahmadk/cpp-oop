// implementation of Point class hierarchy.
// ***use -lm switch with gcc/g++ to link cmath***
#include <iostream>
#include <cmath>    // c math library
#include "Point.h"  // Point class hierarchy definition

using namespace std;

// constructor
Point::Point()
{
    cout << "Abstract base class Point constructor." << endl;
} // end Point constructor

// destructor
Point::~Point()
{
    cout << "Abstract base class Point destructor." << endl;
} // end Point destructor

// constructor
Point2D::Point2D( double xx, double yy ) : x(xx), y(yy)
{
    cout << "constructing a Point2D object: ";
    print();
    cout << endl;
} // end Point2D constructor

// set x coordinate value
Point2D & Point2D::setX( double xx )
{
    x = xx;
    return *this;
} // end function setX

// set x coordinate value
Point2D & Point2D::setY( double yy )
{
    y = yy;
    return *this;
} // end function setY

// return x coordinate value
double Point2D::getX() const
{
    return x;
} // end function getX

// return y coordinate value
double Point2D::getY() const
{
    return y;
} // end function getY

// get squared distance from other point
double Point2D::getSquaredDistance( const Point2D &other ) const
{
    // return squared euclaidean distance between the points
    return (
            pow( ( x - other.x ), 2 ) + pow( ( y - other.y ), 2 ) );
} // end function getDistance

// get distance from other point
double Point2D::getDistance( const Point2D &other ) const
{
    // return euclaidean distance between the points
    return sqrt(
                pow( ( x - other.x ), 2 ) +
                pow( ( y - other.y ), 2 )
            );
} // end function getDistance

// overridden virtual print function with
// class specific implementation
void Point2D::print()
{
    cout << "(" << x << ", " << y << ")";
}

// destructor
Point2D::~Point2D()
{
    cout << "destroying a Point2D object: ";
    print();
    cout << endl;
} // end Point2D destructor

// constructor
Point3D::Point3D(
        double xx, double yy, double zz
    ) : x(xx), y(yy), z(zz)  // initializer list
{
    cout << "constructing a Point3D object.";
    print();
    cout << endl;
} // end Point3D constructor

// set x coordinate value
Point3D & Point3D::setX( double xx )
{
    x = xx;
    return *this;
} // end function setX

// set y coordinate value
Point3D & Point3D::setY( double yy )
{
    y = yy;
    return *this;
} // end function setY

// set z coordinate value
Point3D & Point3D::setZ( double zz )
{
    z = zz;
    return *this;
} // end function setZ

// get x coordinate value
double Point3D::getX() const
{
    return x;
} // end function setX

// get y coordinate value
double Point3D::getY() const
{
    return y;
} // end function setY

// get z coordinate value
double Point3D::getZ() const
{
    return z;
} // end function setZ

// get distance from other point
double Point3D::getDistance( const Point3D &other ) const
{
    // return euclaidean distance between the points
    return sqrt(
                pow( ( x - other.x ), 2 ) +
                pow( ( y - other.y ), 2 ) +
                pow( ( z - other.z ), 2 )
            );
} // end function getDistance

// overridden virtual print function with
// class specific implementation
void Point3D::print()
{
    cout << "(" << x << ", " << y << ", " << z << ")";
} // end function print

// destructor
Point3D::~Point3D()
{
    cout << "destroying a Point3D object: ";
    print();
    cout << endl;
} // end Point3D destructor
