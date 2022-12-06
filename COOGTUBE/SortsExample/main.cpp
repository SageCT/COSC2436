#include <iostream>

using namespace std;

int partition(int *arr, int start, int end)
{
    int pivot = start;
    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i] < arr[start])
        {
            pivot++;
            swap(arr[i], arr[pivot]);
        }
    }
    swap(arr[start], arr[pivot]);
    return pivot;
}

void quickSort(int *arr, int left, int right)
{
    if (left < right)
    {
        int pivot = partition(arr, left, right);
        quickSort(arr, left, pivot - 1);
        quickSort(arr, pivot + 1, right);
    }
}

int main()
{
    int arr[8] = {45, 24, 65, 77, 124, 11, 2, 10};
    quickSort(arr, 0, 7);
    for (int i = 0; i < 8; i++)
        cout << arr[i] << " ";
    return 0;
}