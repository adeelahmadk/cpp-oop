// implementation of Shapes class hierarchy
#include <cmath>     // C math library
#include <cfloat>    // type support library: DBL_MIN, DBL_MAX
#include <iostream>
#include <iomanip>   // I/O manipulators: fixed, setprecision, ...
#include "Point.h"
#include "Shapes.h"

using namespace std;

// initialize static constant pi
const double Shape::PI = 3.14159265358979323846;

// constructor
Shape::Shape()
{
    cout << "Abstract base class Shape constructor." << endl;
} // end Shape constructor

// destructor
Shape::~Shape()
{
    cout << "Abstract base class Shape destructor." << endl;
} // end Shape destructor

// constructor
TwoDimensionalShape::TwoDimensionalShape()
{
    cout << "2nd level abstract class TwoDimensionalShape constructor." << endl;
} // end TwoDimensionalShape constructor

// get volume
double TwoDimensionalShape::getVolume() const
{
    // 2D shapes have zero volume
    return 0;
} // end function getVolume

// destructor
TwoDimensionalShape::~TwoDimensionalShape()
{
    cout << "2nd level abstract class TwoDimensionalShape destructor." << endl;
} //end TwoDimensionalShape destructor

// constructor
ThreeDimensionalShape::ThreeDimensionalShape()
{
    cout << "2nd level abstract class TwoDimensionalShape constructor." << endl;
} // end ThreeDimensionalShape constructor

// get area
double ThreeDimensionalShape::getArea() const
{
    // 3D shapes have zero area
    return 0;
} // end function getArea

// destructor
ThreeDimensionalShape::~ThreeDimensionalShape()
{
    cout << "2nd level abstract class ThreeDimensionalShape destructor." << endl;
} // end ThreeDimensionalShape destructor

// constructor
Circle::Circle( Point2D c, double r ) : center(c), radius(r)
{
    cout << "constructing a Circle object: ";
    print();
    cout << endl;
} // end Circle constructor

// get area
double Circle::getArea() const
{
    return Shape::PI * radius * radius;
} // end function getArea

// get circumference
double Circle::getCircumference() const
{
    return 2 * Shape::PI * radius;
} // end function getCircumference

// print circle information
void Circle::print()
{
    cout << "Circle<c";
    center.print();
    cout << ", r=" << radius << ">";
} // end function print

// destructor
Circle::~Circle()
{
    cout << "destroying a Circle object: ";
    print();
    cout << endl;
} // end Circle destructor

// constructor
Triangle::Triangle( Point2D a, Point2D b, Point2D c ) : vA(a), vB(b), vC(c)
{
    eAB = vA.getDistance( vB );
    eBC = vB.getDistance( vC );
    eCA = vC.getDistance( vA );
    cout << "constructing a Triangle object: ";
    print();
    cout << endl;
} // end Triangle constructor

// get area
double Triangle::getArea() const
{
    double s = ( eAB + eBC + eCA ) / 2;
    // using Heron’s Formula
    return sqrt( s * ( s - eAB ) * ( s - eBC ) * ( s - eCA ) );
} // end function getArea

// get parimeter
double Triangle::getParimeter() const
{
    return ( eAB + eBC + eCA );
} // end function getParimeter

// print circle information
void Triangle::print()
{
    cout << "Triangle<A";
    vA.print();
    cout << ", B";
    vB.print();
    cout << ", C";
    vC.print();
    cout << ">";
} // end function print

// destructor
Triangle::~Triangle()
{
    cout << "destroying a Triangle object: ";
    print();
    cout << endl;
} // end Triangle destructor

// constructor
Rectangle::Rectangle(
        Point2D a, Point2D b, Point2D c, Point2D d ) : vA(a), vB(b), vC(c), vD(d)
{
    if( isRectangle( a, b, c, d ) )
    {
        // order the vertices
        Point2D ptList[4] = { a, b, c, d };
        Pair min = getMin( ptList ); // get minimum x and y
        Pair max = getMax( ptList ); // get maximum x and y
        // initialize vertices
        vA.setX( min.x ).setY( min.y );
        vB.setX( min.x ).setY( max.y );
        vC.setX( max.x ).setY( max.y );
        vD.setX( max.x ).setY( min.y );
    }
    else {
        // initialize vertices with defaults
        vA.setX( 10 ).setY( 10 );
        vB.setX( 10 ).setY( 20 );
        vC.setX( 20 ).setY( 20 );
        vD.setX( 20 ).setY( 10 );
    }
    width = abs( vA.getX() - vC.getX() );
    length = abs( vA.getY() - vC.getY() );

    if( width > length )
    {
        double temp = width;
        width = length;
        length = temp;
    }

    cout << "constructing a Rectangle object: ";
    print();
    cout << endl;
} // end Rectangle constructor

// get area of the rectangle
double Rectangle::getArea() const
{
    return width * length;
} // end function getArea

// get parimeter of the rectangle
double Rectangle::getParimeter() const
{
    return ( ( width * 2 ) + ( length * 2 ) );
} // end function getParimeter

// print rectangle information
void Rectangle::print()
{
    cout << "Rectangle<A";
    vA.print();
    cout << ", B";
    vB.print();
    cout << ", C";
    vC.print();
    cout << ", D";
    vD.print();
    cout << ">";
} // end function print

// destructor
Rectangle::~Rectangle()
{
    cout << "destroying a Rectangle object: ";
    print();
    cout << endl;
} // end Rectangle destructor

// verify if the points constitute vertices of a rectangle
bool Rectangle::isRectangle( Point2D &a, Point2D &b, Point2D &c, Point2D &d )
{
    // get squared distances from point a
    double d2 = a.getSquaredDistance( b );
    double d3 = a.getSquaredDistance( c );
    double d4 = a.getSquaredDistance( d );

    // if there's a repeated point, not valid!
    if( d2 == 0 || d3 == 0 || d4 == 0 ) return false;

    if( d2 > d3 && d2 > d4 )  // if a and b are non-adjacent (form diagonal)
    {
        // if bc and bd are sides of a right-angle triangle
        if( d2 == ( d3 + b.getSquaredDistance( c ) ) &&
            d2 == ( d4 + b.getSquaredDistance( d ) ) )
        {
            // b is diagonal point
            return true;
        }
    }
    else if( d3 > d2 && d3 > d4 )  // if a and c are non-adjacent (form diagonal)
    {
        // if cb and cd are sides of a right-angle triangle
        if( d3 == ( d2 + c.getSquaredDistance( b ) ) &&
            d3 == ( d4 + c.getSquaredDistance( d ) ) )
        {
            // c is diagonal point
            return true;
        }
    }
    else if( d4 > d2 && d4 > d3 )  // if a and d are non-adjacent (form diagonal)
    {
        // if db and dc are sides of a right-angle triangle
        if( d4 == ( d2 + d.getSquaredDistance( b ) ) &&
            d4 == ( d3 + d.getSquaredDistance( c ) ) )
        {
            // d is diagonal point
            return true;
        }
    }

    // if none of above is true then
    // vertices don't form a rectangle
    return false;
}

// get minimum x and y values in the vertices
Pair Rectangle::getMin( const Point2D list[] ) const
{
    // initialize a pair of max. double values
    Pair min = { DBL_MAX, DBL_MAX };
    // iterate the list of vertices
    for( size_t i = 0; i < 4; i++ )
    {
        // update min if a smaller value is encountered
        if( list[i].getX() < min.x ) min.x = list[i].getX();
        if( list[i].getY() < min.y ) min.y = list[i].getY();
    }

    return min;
}

// get maximum x and y values in the vertices
Pair Rectangle::getMax( const Point2D list[] ) const
{
    // initialize a pair of min. double values
    Pair max = { DBL_MIN, DBL_MIN };
    // iterate the list of vertices
    for( size_t i = 0; i < 4; i++ )
    {
        // update max if a bigger value is encountered
        if( list[i].getX() > max.x ) max.x = list[i].getX();
        if( list[i].getY() > max.y ) max.y = list[i].getY();
    }

    return max;
}

//constructor
Sphere::Sphere( Point3D c, double r ) : center( c ), radius( r )
{
    cout << "constructing a Sphere object: ";
    print();
    cout << endl;
} // end Sphere constructor

double Sphere::getSurfaceArea() const
{
    return ( 4.0f * Shape::PI * pow( radius, 2 ) );
}

double Sphere::getVolume() const
{
    return ( ( 4.0f / 3.0f ) * Shape::PI * pow( radius, 3 ) );
}

void Sphere::print()
{
    cout << "Sphere<c";
    center.print();
    cout << ", r=" << radius << ">";
} // end function print

// destructor
Sphere::~Sphere()
{
    cout << "destroying a Sphere object: ";
    print();
    cout << endl;
} // end Sphere destructor
