#include <string>
#include <iostream>

using namespace std;

// Recursion Extras from Workshop

// FIbonnaci sequence
int fibo(int n)
{
    int fib;
    if (n <= 1)
        return n;
    return fibo(n - 1) + fibo(n - 2);
}

// Sum numbers to n
int sum(int n)
{
    if (n <= 1)
        return n;
    return n + sum(n - 1);
}

// Palindrom checker
bool palin(string s, int start, int end)
{
    if ((s[start] != s[end]))
        return false;

    if (((s[start] == s[end]) && (start == end)) || ((end % 2 != 0) && (s[start] == s[end])))
        return true;
    return palin(s, start + 1, end - 1);
}

int main()
{
    cout << palin("tacocat", 0, 6) << endl;
    cout << palin("goof", 0, 3) << endl;
    cout << palin("goog", 0, 3) << endl;
    cout << palin("doog", 0, 3) << endl;
}