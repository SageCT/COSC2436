#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iomanip>
#include "ArgumentManager.h"

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

string computePostfix(string str)
{
    stack<int> s;
    string ans;

    // Computing postFix
    for (int x = 0; x < str.length(); x++)
    {
        if (str.at(x) >= '0' && str.at(x) <= '9')
        {
            string temp = "";
            temp += str.at(x);
            s.push(stoi(temp));
        }
        else if (str.at(x) == 'x')
        {
            s.push(-1);
        }
        else
        {

            int rightNum = s.top();
            s.pop();

            int leftNum = s.top();
            s.pop();

            if (rightNum > -1 && leftNum > -1)
            {
                switch (str.at(x))
                {
                case '+':
                    s.push(leftNum + rightNum);
                    break;
                case '-':
                    s.push(leftNum - rightNum);
                    break;
                case '*':
                    s.push(leftNum * rightNum);
                    break;
                case '/':
                    s.push(leftNum / rightNum);
                    break;
                }
            }
            else if (leftNum < 0 || rightNum < 0)
            {
                if (leftNum < 0)
                {
                    ans += "x";
                    (leftNum > -1) ? (ans += to_string(leftNum)) : (ans += to_string(rightNum));
                    ans += str.at(x);
                }
                else if (rightNum < 0)
                {
                    (leftNum > -1) ? (ans += to_string(leftNum)) : (ans += to_string(rightNum));
                    ans += "x";
                    ans += str.at(x);
                }
            }
        }
    }
    return ans;
}

int main(int argc, char *argv[])
{
    // ArgumentManager am(argc, argv);
    // ifstream input(am.get("input"));
    // ofstream out(am.get("output"));

    ifstream input("input11.txt");
    ofstream out("output1.txt");
    if (input.peek() != EOF)
    {
        string in;
        vector<string> lines;
        stack<char> chars;
        // EXAMPLE INPUT
        // ( 2 + 4 ) * x = 24

        while (getline(input, in))
        {
            in.erase(remove(in.begin(), in.end(), '\n'), in.end());
            in.erase(remove(in.begin(), in.end(), '\r'), in.end());
            in.erase(remove(in.begin(), in.end(), ' '), in.end());
            if (in.size() == 0)
                continue;
            lines.push_back(in);
        }

        for (int x = 0; x < lines.size(); x++)
        {
            string line = lines.at(x).substr(0, lines.at(x).find("="));
            double rightSide = stoi(lines.at(x).substr(lines.at(x).find("=") + 1, (lines.at(x).find("=")) - (lines.at(x).length() - 1)));

            double ans = 0;
            string postFix = toPostFix(line);
            cout << postFix << endl;
            postFix = computePostfix(postFix);

            if (postFix.find("*") != string::npos)
            {
                //Isolating the number on the left side of the equation.
                string temp = "";
                for (auto ans : postFix)
                    if (isdigit(ans))
                        temp += ans;
                double num = stoi(temp);

                ans = (double)rightSide / (double)num;
            }

            else if (postFix.find("/") != string::npos)
            {
                //Isolating the number on the left side of the equation.
                string temp = "";
                for (auto ans : postFix)
                    if (isdigit(ans))
                        temp += ans;
                double num = stoi(temp);

                //Depending on what character is first aka the number or x, multiply or divide the other side.
                if (isdigit(postFix.at(0)))
                    ans = (double)num / (double)rightSide;
                else if (postFix.at(0) == 'x')
                    ans = (double)rightSide * (double)num;
            }

            else if (postFix.find("+") != string::npos)
            {
                //Isolating the number on the left side of the equation.
                string temp = "";
                for (auto ans : postFix)
                    if (isdigit(ans))
                        temp += ans;
                double num = stoi(temp);

                ans = (double)rightSide - (double)num;
            }

            else if (postFix.find("-") != string::npos)
            {

            }

            cout << std::setprecision(2) << std::fixed;
            cout << postFix << endl;
            cout << ans << endl;
        }
    }
}