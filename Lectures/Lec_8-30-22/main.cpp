#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void pp(int n)
{
    if (0 == n)
        return;
    pp(n - 1);
    cout << n << endl;
}

// Print out string array recursively
void rA(string n[], int i)
{
    
        
        
}

int main()
{
    // int n[] = {1, 2, 3, 4, 5, 6};
    // rA(n);
    return 0;

    int a = 10;
    cout << "slowww" << a << endl;

    int *p = &a;
    cout << "fast ..." << *p << endl;
    cout << "memory address..." << p << endl;
    p = nullptr;
    p = new int; // a;;pcatopm + address into p
    *p = 222;
    cout << *p << endl;
    delete p;
    p = new int[4];

    for (int i; i < 4; i++)
        p[i] = i * 10;
    for (int i = 0; i < 4; i++)
    {
    }
}