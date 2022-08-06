// Commission employee class hierarchy.
// Display order in which base-class and derived-class
// constructors and destructors are called.
#include <iostream>
#include <iomanip>
#include "BasePlusCommissionEmployee.h" // class definition
// including BasePlusCommissionEmployee.h in turn
// includes CommissionEmployee.h
using namespace std;

int main()
{
    // set floating-point output formatting
    cout << fixed << setprecision( 2 );

    { // begin new scope
        // instantiate a CommissionEmployee object
        CommissionEmployee employee1(
                "Muhammad",         // first name
                "Faizan",           // last name
                "33333-4444444-5",  // NIC number
                5000,               // gross sale
                .04                 // commission rate
            );
        // print weekly earnings
        cout << employee1.getFirstName() << " " << employee1.getLastName() << ": "
            << " current week's earnings are $"
            << employee1.earnings() << endl;

        cout << endl;
    } // end scope

    cout << endl;
    // instantiate a BasePlusCommissionEmployee object
    BasePlusCommissionEmployee employee2(
            "Raiqa",            // first name
            "Ahmed",            // last name
            "55555-6666666-7",  // NIC number
            2000,               // gross monthly sale
            .06,                // commission rate
            800                 // base salary
        );
    // print weekly earnings
    cout << employee2.getFirstName() << " " << employee2.getLastName() << ": "
        << " current week's earnings are $"
        << employee2.earnings() << endl;

    cout << endl;
    // instantiate a BasePlusCommissionEmployee object
    BasePlusCommissionEmployee employee3(
            "Abdul", "Samad", "88888-2222222-8", 8000, .15, 2000 );
    // print weekly earnings
    cout << employee3.getFirstName() << " " << employee3.getLastName() << ": "
        << " current week's earnings are $"
        << employee3.earnings() << endl;

    cout << endl;

    // Test: try to call an overridden function with a base class
    // pointer pointing to a derived class object
    cout << setfill('=') << setw(60) << " " << endl;
    cout << "**Access Derived calss interface with its own object**"
        <<endl;
    cout << employee2.getFirstName() << " " << employee2.getLastName() << ": "
        << " current week's earnings are $"
        << employee2.earnings() << endl;
    cout << "\n**Reference Derived calss object with Base class pointer**"
        << "\n**and trying to access the same public interface**"
        <<endl;
    // instantiate a pointer to CommissionEmployee object and point
    // it to a BasePlusCommissionEmployee object: employee2
    CommissionEmployee *commEmpPtr = &employee2;
    // now try to call public interface using the pointer
    cout << commEmpPtr->getFirstName() << " " << commEmpPtr->getLastName() << ": "
        << " current week's earnings are $"
        << commEmpPtr->earnings() << endl;
    cout << "\n**What just happened? Try to explain it!**\n"
        << "**What can we do to solve this?**" << endl;
    cout << setfill('=') << setw(60) << " " << endl;

    cout << endl;
} // end main
