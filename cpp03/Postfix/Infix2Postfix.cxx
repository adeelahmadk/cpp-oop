/* C++ implementation to convert
infix expression to postfix*/

#include <iostream>
#include <ostream>
#include <string>
#include <cmath>
#include "Stack.h"
using namespace std;

// Function to return precedence of operators
int precedenceLevel(char c)
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
                && precedenceLevel(s[i]) <= precedenceLevel(st.peek())) {
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

int evalBinaryOp( int x, int y, char op ) {
    int acc = 0;
    switch (op) {
    case '+':
        acc = x + y;
        break;
    case '-':
        acc = x - y;
        break;
    case '*':
        acc = x * y;
        break;
    case '^':
        acc = pow(x, y);
        break;
    default:
        break;
    }

    return acc;
}

int evalPostfix( string expr, int params[], int paramCount )
{
    Stack<int> st; // For stack operations
    int result = 0, temp, a, b;
    char c;

    for (int i = 0; i < expr.length(); i++) {
        c = expr[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            int n = (c >= 'A' && c <= 'Z')? c - 'A' : c - 'a';
            st.push(params[n]);
            cout << c << "> pushed: " << params[n] << endl;
        } else {
            b = st.peek();
            st.pop(temp);
            cout << "> popped: " << b << endl;
            a = st.peek();
            st.pop(temp);
            cout << "> popped: " << a << endl;
            int r = evalBinaryOp(a, b, c);
            st.push(r);
            cout << "> pushed: " << r << endl;
        }
    }
    result = st.peek();

    return result;
}

// Driver program to test above functions
int main()
{
    string expr = "a+b*(c^d-e)^(f+g*h)-i";  // abcd^e-fgh*+^*+i-
    int params[9] = { 8, 2, 2, 3, 5, 1, 2, 2, 122 }; /* "8+5*(2^3-5)^(2+2*3)-22" */
    string result = infixToPostfix(expr);
    cout<< "Infix: " << expr << endl
        << "Postfix: " << result << endl;
    int num = evalPostfix(result, params, 9);
    cout << "Evaluation: " << num << endl;
    return 0;
}

