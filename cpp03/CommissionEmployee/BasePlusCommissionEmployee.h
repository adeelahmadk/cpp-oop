// BasePlusCommissionEmployee.h
// BasePlusCommissionEmployee class derived from
// CommissionEmployee class.
//               Base Class
//          {CommissionEmployee}
//                |
//      {BasePlusCommissionEmployee}  (concrete class)

#ifndef BASEPLUS_H
#define BASEPLUS_H

#include "CommissionEmployee.h" // CommissionEmployee class declaration
// Header file for C++ standard string class is already
// included in CommissionEmployee.h
using namespace std;

class BasePlusCommissionEmployee : public CommissionEmployee
{
public:
   BasePlusCommissionEmployee( const string &, const string &,
      const string &, double = 0.0, double = 0.0, double = 0.0 );
   ~BasePlusCommissionEmployee(); // destructor

   void setBaseSalary( double ); // set base salary
   double getBaseSalary() const; // return base salary

   double earnings() const; // calculate earnings
   void print() const; // print BasePlusCommissionEmployee object
private:
   double baseSalary; // base salary
}; // end class BasePlusCommissionEmployee

#endif
