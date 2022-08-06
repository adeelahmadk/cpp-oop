// Point.h
// Point class hierarchy definition including:
//        Abstract Base Class (abc) 
//                 {Point}
//                /       \
//          {Point2D}   {Point3D}  (concrete classes)

#ifndef POINT_H
#define POINT_H

// base class
class Point
{
public:
    Point(); // constructor
    // virtual destructor
    virtual ~Point(); // destructor
    // pure virtual function to make Point an abstract class
    // now object of type Point can't be instantiated
    virtual void print() = 0;
}; // end class Point

class Point2D : public Point
{
public:
    Point2D(double, double); // constructor
    Point2D &setX( double ); // set x value
    Point2D &setY( double ); // set y value
    double getX() const; // get x value
    double getY() const; // get y value
    double getSquaredDistance( const Point2D & ) const; // get sqr of distance from another point
    double getDistance( const Point2D & ) const; // get distance from another point
    void print(); // override (virtual) print function
    ~Point2D(); // destructor
private:
    double x; // x coordinate value
    double y; // y coordinate value
};

class Point3D : public Point
{
public:
    Point3D(double, double, double); //constructor
    Point3D &setX( double ); // set x value
    Point3D &setY( double ); // set y value
    Point3D &setZ( double ); // set z value
    double getX() const; // get x value
    double getY() const; // get y value
    double getZ() const; // get z value
    double getDistance( const Point3D & ) const; // get distance from another point
    void print(); // override (virtual) print function
    ~Point3D(); // destructor
private:
    double x; // x coordinate value
    double y; // y coordinate value
    double z; // z coordinate value
};

#endif
