// INFIX TO POSTFIX CONVERSION
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int priority(char c)
{
    if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

string infixToPostfix(string s)
{
    stack<char> st;
    string postfix;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
        }

        else if (isdigit(s[i]))
            postfix += s[i];

        else if (s[i] == '(')
            st.push('(');

        else if (s[i] == ')')
        {
            while (st.top() != '(')
            {
                postfix += st.top();
                st.pop();
            }
            st.pop();
        }

        else
        {
            while (!st.empty() && priority(s[i]) <= priority(st.top()))
            {
                postfix += st.top();
                st.pop();
            }
            st.push(s[i]);
        }
    }

    while (!st.empty())
    {
        postfix += st.top();
        st.pop();
    }
    return postfix;
}

double evaluatePostfix(string s)
{
    stack<double> st;

    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]))
            st.push(s[i] - '0');
        else
        {
            double val2 = st.top();
            st.pop();

            double val1 = st.top();
            st.pop();

            switch (s[i])
            {
            case '+':
                st.push(val1 + val2);
                break;
            case '-':
                st.push(val1 - val2);
                break;
            case '*':
                st.push(val1 * val2);
                break;
            case '/':
                st.push(val1 / val2);
                break;
            }
        }
    }
    return st.top();
}

int main()
{
    string s = "(2/4)*5+(6*7)";
    s = infixToPostfix(s);
    cout << "Pre-evaluation: " << s << endl;
    cout << "Post-evaluation: " << evaluatePostfix(s) << endl;
    return 0;
}