// SalesPerson class definition.
// Member functions defined in SalesPerson.cpp.
#ifndef SALESP_H
#define SALESP_H

#include <cstddef>

class SalesPerson
{
public:
    static const int monthsPerYear = 12; // months in one year
    static const size_t nameLength = 50; // max length for first & last names
    SalesPerson(const char * const = "John", const char * const = "Doe"); // constructor
    void getSalesFromUser(); // input sales from keyboard
    void setSales( int, double ); // set sales for a specific month
    void printAnnualSales(); // summarize and print sales
private:
    double totalAnnualSales(); // prototype for utility function
    double sales[ monthsPerYear ]; // 12 monthly sales figures
    char firstName[nameLength]; // Sales person's first name
    char lastName[nameLength]; // Sales person's last name
}; // end class SalesPerson

#endif
