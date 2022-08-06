// Shapes driver program.
// use of header "cmath" requires explicit option to g++
// ***use -lm switch with gcc/g++ to link cmath***
#include <iostream>
#include <iomanip>  // I/O manipulators
#include "Point.h"
#include "Shapes.h"

using namespace std;

int main()
{
    // set floating-point output formatting
    cout << fixed << setprecision( 2 );

    // instantiating an object of child class
    // observe the order of constructor calls
    Point2D p1( 2, 3 );

    cout << "2D point p1 is defined as: ";
    // calling a member function with the object
    p1.print();
    cout << endl;

    cout << endl;

    // instantiating an object of child class Circle.
    // constructor takes a Point2D object & a double,
    // watch the constructor call pattern carefully.
    Circle c1( Point2D( 2, 1 ), 1.50 );
    // after the private data member in Circle is
    // initialized, the life-time of the Point2D
    // object passed to the constructor is over.
    // watch the destructor calls at the end of the
    // Circle constructor.

    cout << endl;

    cout << "Circle c1 is defined as: ";
    c1.print();
    cout << endl;
    cout << "  Circumference = " << c1.getCircumference()
        << endl
        << "  Area = " << c1.getArea() << endl;
    cout << "where PI = " << setprecision(10) << Shape::PI
        << setprecision(2) << endl;

    cout << endl;

    // define a pointer to the abstract base class
    // and point it to a (child) circle object
    Shape *abptr = &c1;
    cout << "Calling virtual functions with abstract base class pointer:"
        << endl
        << "  Print: ";
    abptr->print();  // call virtual print function
    cout << endl
        << "  Area = " << abptr->getArea()  // call virtual getArea function
        << endl;

    cout << endl;

    // instantiate a Triangle object
    Triangle t1(
                Point2D(0, 0),
                Point2D( 1, 1 ),
                Point2D( 1, 0 )
            );

    cout << endl;

    // call public interface
    cout << "Triangle t1 is defined as: ";
    t1.print();
    cout << endl;
    cout << "  Area = " << t1.getArea() << endl
        << "  Parimeter = " << t1.getParimeter() << endl;

    cout << endl;

    // instantiate a Rectangle object
    Rectangle r1(
                Point2D(1, 1),
                Point2D( 6, 5 ), // sending vertices out of order
                Point2D( 1, 5 ),
                Point2D( 6, 1 )
            );

    cout << endl;

    // call public interface
    cout << "Rectangle r1 is defined as: ";
    r1.print();
    cout << endl;
    cout << "  Area = " << r1.getArea() << endl
        << "  Parimeter = " << r1.getParimeter() << endl;

    cout << endl;

    // Try to instantiate a Rectangle object
    // with vertices that make a trapoziod
    Rectangle r2(
            Point2D(1, 1),
            Point2D( 6, 5 ),
            Point2D( 1, 5 ),
            Point2D( 7, 1 )  // vertix that doesn't make a right angle
        );

    cout << endl;

    // call public interface
    cout << "Rectangle r2 is defined as: ";
    r2.print();
    cout << endl;
    cout << "  Area = " << r2.getArea() << endl
        << "  Parimeter = " << r2.getParimeter() << endl;

    cout << endl;

    // Try to instantiate a Rectangle object
    // with vertices that make a trapoziod
    Sphere sp1(
            Point3D(20, 20, 20), 5
        );

    cout << endl;

    // call public interface
    cout << "Sphere sp1 is defined as: ";
    sp1.print();
    cout << endl;
    cout << "  Surface Area = " << sp1.getSurfaceArea() << endl
        << "  Volume = " << sp1.getVolume() << endl;

    cout << endl;

    return 0;
}
