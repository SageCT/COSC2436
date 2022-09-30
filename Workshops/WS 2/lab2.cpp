#include <string>
#include <iostream>

using namespace std;

/*bool validateTarget(int **matrix, bool **visited, int target, int x, int y, int currentCount, int maxX, int maxY)
{
    // Conditions to return false

    // Visited
    visited[x][y] = true;

    // Change your currentCount

    // Condition to return true

    // Recursive calls for every path
    if (true) // You have your recursive calls here to go to every single path
        return true;

    // back track
    visited[x][y] = false; // This is the back tracking. It allows you to reuse

    return false;
}
*/

void resizeArr(int *&arr, int &curSize)
{
    // implement your code here
    int *newArr = new int[curSize * 2];

    for (int x = 0; x < curSize; x++)
    {
        int numb = arr[x];
        newArr[x] = numb;
    }

    delete[] arr;
    arr = newArr;
}

void print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
}

int main()
{
    int size = 5;
    int *arr = new int[5];

    print(arr, size);
    resizeArr(arr, size);
    print(arr, size);

    delete[] arr;
    return 0;
}
