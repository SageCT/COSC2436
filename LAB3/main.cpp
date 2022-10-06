#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;

void multiply(string &eqtn)
{
    float leftInt = (float)stoi(eqtn.substr(0, eqtn.find('*'))), rightInt = (float)stoi(eqtn.substr(eqtn.find('*') + 1, eqtn.length() - 1));
    eqtn = to_string(leftInt * rightInt);
}

void divide(string &eqtn)
{
    float leftInt = (float)stoi(eqtn.substr(0, eqtn.find('/'))), rightInt = (float)stoi(eqtn.substr(eqtn.find('/') + 1, eqtn.length() - 1));
    eqtn = to_string(leftInt / rightInt);
}

void add(string &eqtn)
{
    float leftInt = (float)stoi(eqtn.substr(0, eqtn.find('+'))), rightInt = (float)stoi(eqtn.substr(eqtn.find('+') + 1, eqtn.length() - 1));
    eqtn = to_string(leftInt + rightInt);
}

void subtract(string &eqtn)
{
    float leftInt = (float)stoi(eqtn.substr(0, eqtn.find('-'))), rightInt = (float)stoi(eqtn.substr(eqtn.find('-') + 1, eqtn.length() - 1));
    eqtn = to_string(leftInt - rightInt);
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

        for (auto line : lines)
        {
            for (int i = line.length() - 1; i >= 0; i--)
            {
                chars.push(line.at(i));
            }

            while (!chars.empty())
            {
                if (chars.top() == '(')
                {

                    stack<char> temp(chars);
                    string eqtn;
                    temp.pop();

                    while (temp.top() != ')')
                    {
                        eqtn += temp.top();
                        temp.pop();
                    }
                    std::cout << eqtn << std::endl;
                    if (eqtn.find('*') != string::npos)
                    {
                        multiply(eqtn);
                        std::cout << eqtn << std::endl;
                    }

                    else if (eqtn.find('/') != string::npos)
                    {
                        divide(eqtn);
                        cout << eqtn << std::endl;
                    }

                    else if (eqtn.find('+') != string::npos)
                    {
                        add(eqtn);
                        cout << eqtn << std::endl;
                    }

                    else if (eqtn.find('-') != string::npos)
                    {
                        subtract(eqtn);
                        cout << eqtn << std::endl;
                    }
                }
                chars.pop();
            }
        }
    }
}