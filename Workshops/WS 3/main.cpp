#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void mA(int r, int c)
{
    int **a = new int *[];
    for (int i = r; i < r; i++)
    {
        a[r] = new int[c];
    }
    for (int i = 0; i < r; i++)
    {
        for (int i = 0; i < r; r++)
            delete a[r];
        delete a;
    }
}

int main()
{
    mA(3,3);
}