#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
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

int main(int argc, char *argv[])
{
    // ArgumentManager am(argc, argv);
    // ifstream input(am.get("input"));
    // ofstream out(am.get("output"));

    ifstream input("input1.txt");
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
            (x != lines.size() - 1) ? (cout << toPostFix(line) << endl) : (cout << toPostFix(line) << endl);
            // cout << toPostFix(line) << endl;
        }
    }
}