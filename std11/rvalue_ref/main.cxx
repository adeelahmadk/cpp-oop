/**
* @file init_list/main.cxx
* @author Adeel Ahmad (6880680+adeelahmadk@users.noreply.github.com)
* @brief Example demonstrating c++11 rvalue reference and move semantics
* @version 0.1
* @date 2023-06-09
*
* @copyright Copyright (c) 2023
*
*/
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <limits>
using std::ostream;
using std::cout;
using std::endl;
using std::vector;
using std::string;

class Holder
{
public:

  Holder(int size)         // Constructor
  {
    m_data = new int[size];
    m_size = size;

    cout << "Default Constructor" << endl;
  }

  Holder(const Holder& other)   // Copy Constructor
  {
    m_data = new int[other.m_size];  // (1)
    for ( size_t i = 0; i < other.m_size; ++i ) {  // (2)
        m_data[i] = other.m_data[i];
    }
    m_size = other.m_size;

    cout << "Copy Constructor" << endl;
  }

  Holder(Holder&& other)     // Move Constructor
  {         // ^-- rvalue reference in input
    m_data = other.m_data;   // (1)
    m_size = other.m_size;   // move rvalue reference to lvalue
    other.m_data = nullptr;  // (2)
    other.m_size = 0;

    cout << "Move Constructor" << endl;
  }

  Holder& operator=(const Holder& other)  // copy assignment operator 
  {
     if(this == &other) return *this;  // (1)

    delete[] m_data;  // (2)

    m_data = new int[other.m_size];
    for ( size_t i = 0; i < other.m_size; ++i ) {
        m_data[i] = other.m_data[i];
    }
    m_size = other.m_size;

    cout << "Copy Assignment" << endl;

    return *this;  // (3)
  }

  Holder& operator=(Holder&& other)     // move assignment operator
  {                    // ^-- rvalue reference in input
    if (this == &other) return *this;

    delete[] m_data;         // (1)

    m_data = other.m_data;   // (2)
    m_size = other.m_size;

    other.m_data = nullptr;  // (3)
    other.m_size = 0;

    cout << "Move Assignment" << endl;

    return *this;
  }

  size_t size() { return m_size; }

  int at(const size_t &index) {
    if ( index >= m_size )
      return std::numeric_limits<int>::min();

    return m_data[index];
  }

  ~Holder()                // Destructor
  {
    delete[] m_data;
  }

private:

  int*   m_data;
  size_t m_size;
};

Holder createHolder(int size)
{
  return Holder(size);
}

int main (int argc, char *argv[])
{
  cout << "Testing move semantics:\n";

  Holder h1(1000);                // regular constructor
  Holder h2(h1);                  // copy constructor (lvalue in input)
  Holder h3 = createHolder(2000); // move constructor (rvalue in input) (1) 

  h2 = h3;                        // assignment operator (lvalue in input)
  h2 = createHolder(500);         // move assignment operator (rvalue in input)

  cout << "\n" << "Testing 2 versions of vector::pushback" << endl;

  string str = "Salt";
  vector<string> v;

  // uses the push_back(const T&) overload, which means 
  // we'll incur the cost of copying str
  v.push_back(str);
  cout << "After copy, str is \"" << str << "\"\n";

  // uses the rvalue reference push_back(T&&) overload, 
  // which means no strings will be copied; instead, the contents
  // of str will be moved into the vector. This is less
  // expensive, but also means str might now be empty.
  v.push_back(std::move(str));  // convert lvalue into rvalue, call "move-version"
  cout << "After move, str is \"" << str << "\"\n";

  cout << "The contents of the vector are { \"" << v[0] << "\""
    << ", \"" << v[1] << "\" }\n"; 

  return 0;
}
