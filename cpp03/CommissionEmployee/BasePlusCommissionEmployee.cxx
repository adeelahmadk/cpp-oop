// BasePlusCommissionEmployee.cpp
// BasePlusCommissionEmployee class implementation.
#include <iostream>
#include "BasePlusCommissionEmployee.h" // class definition
using namespace std;

// constructor
BasePlusCommissionEmployee::BasePlusCommissionEmployee(
        const string &first,
        const string &last,
        const string &cnicn,
        double sales,
        double rate,
        double salary )
   // explicitly call base-class constructor
   : CommissionEmployee( first, last, cnicn, sales, rate )
{
   setBaseSalary( salary ); // validate and store base salary

   cout << "BasePlusCommissionEmployee constructor: " << endl;
   print();
   cout << "\n\n";
} // end BasePlusCommissionEmployee constructor

// destructor
BasePlusCommissionEmployee::~BasePlusCommissionEmployee()
{
   cout << "BasePlusCommissionEmployee destructor: " << endl;
   print();
   cout << "\n\n";
} // end BasePlusCommissionEmployee destructor

// set base salary
void BasePlusCommissionEmployee::setBaseSalary( double salary )
{
   baseSalary = ( salary < 0.0 ) ? 0.0 : salary;
} // end function setBaseSalary

// return base salary
double BasePlusCommissionEmployee::getBaseSalary() const
{
   return baseSalary;
} // end function getBaseSalary

// calculate earnings
double BasePlusCommissionEmployee::earnings() const
{
   return getBaseSalary() + CommissionEmployee::earnings();
} // end function earnings

// print BasePlusCommissionEmployee object
void BasePlusCommissionEmployee::print() const
{
   cout << "base-salaried ";

   // invoke CommissionEmployee's print function
   CommissionEmployee::print();

   cout << "\nbase salary: " << getBaseSalary();
} // end function print
