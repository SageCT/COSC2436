#include <iostream>
#include "ArgumentManager.h"
#include <string>

using namespace std;

int main()
{
    string str = "Hello World";
    cout << str.size() << endl;

    string temp = str.substr(0, 5);
}