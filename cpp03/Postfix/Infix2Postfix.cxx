/* C++ implementation to convert
infix expression to postfix*/

#include <iostream>
#include <ostream>
#include <string>
#include "Stack.h"
using namespace std;

// Function to return precedence of operators
int prec(char c)
{
	if (c == '^')
		return 3;
	else if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

// The main function to convert infix expression
// to postfix expression
string infixToPostfix(string s)
{

	Stack<char> st; // For stack operations, we are using
					// C++ built in stack
	string result;
    char temp;

	for (int i = 0; i < s.length(); i++) {
		char c = s[i];

		// If the scanned character is
		// an operand, add it to output string.
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9'))
			result += c;

		// If the scanned character is an
		// ‘(‘, push it to the stack.
		else if (c == '(')
			st.push('(');

		// If the scanned character is an ‘)’,
		// pop and to output string from the stack
		// until an ‘(‘ is encountered.
		else if (c == ')') {
			while (st.peek() != '(') {
				result += st.peek();
				st.pop(temp);
			}
			st.pop(temp);
		}

		// If an operator is scanned
		else {
			while (!st.isEmpty()
				&& prec(s[i]) <= prec(st.peek())) {
				if (c == '^' && st.peek() == '^')
					break;
				else {
					result += st.peek();
					st.pop(temp);
				}
			}
			st.push(c);
		}
	}

	// Pop all the remaining elements from the stack
	while (!st.isEmpty()) {
		result += st.peek();
		st.pop(temp);
	}

    return result;
}

// Driver program to test above functions
int main()
{
	string exp = "a+b*(c^d-e)^(f+g*h)-i";
	string result = infixToPostfix(exp);
    cout<< "Infix: " << exp << endl
        << "Postfix: " << result << endl;
	return 0;
}


