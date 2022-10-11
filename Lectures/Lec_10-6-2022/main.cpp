// Questions on the exam
// Stack as Array
// Template stack
// Stack as Linkedlist

// Look up Infix to Postfix Expression
// Look up evaluate postfix expression
// If you can do infix to postfix send an email to Rizk by Monday for extra points

// Extras - Write a program to verify if the expression is balanced

// Below is Infix to Postfix Expression
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iomanip>

using namespace std;

int priority(char l)
{
    if (l == '*' || l == '/')
        return 2;
    else if (l == '+' || l == '-')
        return 1;
    else
        return -1;
}

string toPostFix(string str)
{
    stack<char> s;
    string result = "";

    // EXAMPLE INPUT
    // ( 2 + 4 ) * x = 24

    for (int x = 0; x < str.length(); x++)
    {
        if (isdigit(str.at(x)) || str.at(x) == 'x')
            result += str.at(x);
        else if (str.at(x) == '(')
            s.push('(');
        else if (str.at(x) == ')')
        {
            while (s.top() != '(')
            {
                result += s.top();
                s.pop();
            }
            s.pop();
        }
        else
        {
            while (!s.empty() && priority(str.at(x)) <= priority(s.top()))
            {
                result += s.top();
                s.pop();
            }
            s.push(str.at(x));
        }
    }
    while (!s.empty())
    {
        result += s.top();
        s.pop();
    }
    return result;
}

int main()
{
    string in;
    vector<string> lines;
    stack<char> chars;
    // EXAMPLE INPUT
    // ( 2 + 4 ) * x = 24

    lines.push_back("(2+4)*x=24");

    for (int x = 0; x < lines.size(); x++)
    {
        string line = lines.at(x).substr(0, lines.at(x).find("="));
        double rightSide = stoi(lines.at(x).substr(lines.at(x).find("=") + 1, (lines.at(x).find("=")) - (lines.at(x).length() - 1)));

        double ans = 0;
        string postFix = toPostFix(line);
        cout << postFix << endl;
    }
}