#include <iostream>

// Recursive function example
using namespace std;

void printmyname(int c)
{
    if (c == 10)
        return;
    {
        // call same function
        cout << "myname\n"; // read myname
        printmyname(c + 1);
    }
}

int factorial(int n)
{
    if (n == 1)
        return n;
    return n * factorial(n - 1);
}

int multiplynumb(int a, int b)
{
    if (a == 2)
        return a;
    return b + multiplynumb(a - 1, b);
}

void cut(int n)
{
    int helper = 10000;
    int r = 0;
    if (n == 0)
        return;

    cout << n / helper;
    r = n % helper;
    helper /= 10;
    cut(r);
}

int main()
{
    int k = 0;
    printmyname(k);
}
