#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char *argv[])
{
    // ArgumentManager am(argc, argv);
    // ifstream input(am.get("input"));
    // ofstream out(am.get("output"));

    ifstream input("input1.txt");
    ofstream out("output1.txt");
    if (input.peek() != EOF)
    {
        vector<string> lines;
        string in;

        while (getline(input, in))
        {
            in.erase(remove(in.begin(), in.end(), '\n'), in.end());
            in.erase(remove(in.begin(), in.end(), '\r'), in.end());
            in.erase(remove(in.begin(), in.end(), ' '), in.end());
            if (in.size() == 0)
                continue;
            lines.push_back(in);
        }
    }