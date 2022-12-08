#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>

// ty fam
using namespace std;
void print(int *arr, int length)
{
  for (int i = 0; i < length - 1; i++)
  {
    cout << arr[i] << ", ";
  }
  cout << arr[length - 1] << endl;
}

void bubbleSortV1(int *arr, int length)
{
  for (int i = length - 1; i >= 1; i--)
  {
    for (int j = 1; j <= i; j++)
    {
      if (arr[j - 1] > arr[j])
      {
        swap(arr[j], arr[j - 1]);
        // cout << i << "step : ";
        // print(arr,length);
      }
    }
  }
}

void bubbleSortV2(int *arr, int length)
{
  for (int i = length - 1; i >= 1; i--)
  {
    bool is_sorted = true;
    for (int j = 1; j <= i; j++)
    {
      if (arr[j - 1] > arr[j])
      {
        swap(arr[j], arr[j - 1]);
        is_sorted = false;
        // cout << i << "step : ";
        // print(arr,length);
      }
    }
    if (is_sorted)
    {
      return;
    }
  }
}

void selectionSort(int *arr, int length)
{
  for (int i = length - 1; i >= 1; i--)
  {
    int maxIdx = i;
    for (int j = 0; j < i; j++)
    {
      if (arr[j] >= arr[maxIdx])
      {
        maxIdx = j;
      }
    }
    swap(arr[i], arr[maxIdx]);
    // cout << i << "step : ";
    // print(arr,length);
  }
}

int partition(int *arr, int start, int end)
{
  int pivot = start;
  for (int i = start + 1; i <= end; i++)
  {
    if (arr[i] < arr[start])
    {
      pivot++;
      swap(arr[i], arr[pivot]); // important
    }
  }
  swap(arr[start], arr[pivot]);
  return pivot;
}
void quickSort(int *arr, int low, int high)
{
  if (high > low)
  {
    int pivot = partition(arr, low, high);
    quickSort(arr, low, pivot - 1);
    quickSort(arr, pivot + 1, high);
  }
}
void insertionSort(int *arr, int length)
{
  for (int i = 1; i < length; i++)
  {
    int next = arr[i];
    int j;
    for (j = i - 1; j >= 0 && arr[j] > next; j--)
    {
      arr[j + 1] = arr[j];
      // cout<<"In second for"<<endl;
      // print(arr,length);
    }
    arr[j + 1] = next;
    // cout<<"In first for"<<endl;
    // print(arr,length);
  }
}

void merge(int *arr, int low, int mid, int high)
{
  int n = (high - low) + 1;
  int *b = new int[n];
  int left = low;
  int right = mid + 1;
  int bIdx = 0;
  while (left <= mid && right <= high)
  {
    if (arr[left] <= arr[right])
    {
      b[bIdx++] = arr[left++];
    }
    else
    {
      b[bIdx++] = arr[right++];
    }
  }
  while (left <= mid)
  {
    b[bIdx++] = arr[left++];
  }
  while (right <= high)
  {
    b[bIdx++] = arr[right++];
  }
  for (int i = 0; i < n; i++)
  {
    arr[low + i] = b[i];
  }
  delete[] b;
}
void mergeSort(int *arr, int low, int high)
{
  if (low < high)
  {
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
  }
}
int findMax(int *arr, int length)
{
  int max = arr[0];
  for (int i = 1; i < length; i++)
  {
    if (max < arr[i])
    {
      max = arr[i];
    }
  }
  return max;
}
int power(int base, int power)
{
  int result = base;
  for (int i = 0; i < power - 1; i++)
  {
    result *= base;
  }
  return result;
}
void radixSort(int *arr, int size)
{
  int max = findMax(arr, size);
  queue<int> *qarr = new queue<int>[10];
  int maxNumDigits = to_string(max).length();
  int numDigits = 0;
  while (numDigits < maxNumDigits)
  {
    int num = 0;
    int digit = 0;
    for (int i = 0; i < size; i++)
    {
      if (numDigits > 0)
      {
        num = arr[i] / power(10, numDigits);
        // 327 / 10 = 32 327/100 = 3 32

        // cout << "Num: " << power(10, numDigits) << endl;
      }
      else
      {
        num = arr[i];
      }
      digit = num % 10;
      // cout << "digit: " << digit << endl;
      qarr[digit].push(arr[i]);
    }
    int index = 0;
    for (int i = 0; i < 10; i++)
    {
      if (!qarr[i].empty())
      {
        while (!qarr[i].empty())
        {
          arr[index] = qarr[i].front();
          index++;
          qarr[i].pop();
        }
      }
    }
    // cout << "Numdigit is " << numDigits << endl;
    // print(arr, size+1);
    numDigits++;
  }
}

void rizkSort(int A[], int size)
{
  // Creates 10 buckets
  vector<queue<int>> buckets;
  for (int i = 0; i < 10; i++)
  {
    queue<int> queue;
    buckets.push_back(queue);
  }

  // Find largest number
  int max = A[0];
  for (int i = 1; i < size; i++)
  {
    if (A[i] > max)
    {
      max = A[i];
    }
  }

  // Finds number of digits in largest number
  int length = 1;
  if (max > 0)
  {
    for (length = 0; max > 0; length++)
    {
      max = max / 10;
    }
  }

  // Fill buckets
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < size; j++)
    {
      int power = pow(10, i + 1);
      int divisor = pow(10, i);
      int temp = A[j] % power;
      temp = temp / divisor;

      buckets.at(temp).push(A[j]);
    }

    // Empty buckets
    int k = 0;
    for (int j = 0; j < 10; j++)
    {
      while (!buckets.at(j).empty())
      {
        int temp = buckets.at(j).front();
        buckets.at(j).pop();
        A[k++] = temp;
      }
    }
  }
}

void bucketSort(int *arr, int size)
{
  // int max = findMax(arr, size);
  vector<int> *qarr = new vector<int>[size];
  for (int i = 0; i < size; i++)
  {
    if (arr[i] > size)
    {
      qarr[size - 1].push_back(arr[i]);
    }
    else
    {
      qarr[arr[i]].push_back(arr[i]);
    }
  }
  int index = 0;
  for (int q = 0; q < size; q++)
  {
    sort(qarr[q].begin(), qarr[q].end());
  }
  for (int q = 0; q < size; q++)
  {
    for (int i = 0; i < qarr[q].size(); i++)
    {
      arr[index++] = qarr[q][i];
    }
  }
}

void heapify(int *arr, int low, int high)
{
  int largeIndex = 2 * low + 1;
  while (largeIndex <= high)
  {
    if (largeIndex < high)
    {
      if (arr[largeIndex] < arr[largeIndex + 1])
      {
        largeIndex++;
      }
    }
    if (arr[low] > arr[largeIndex])
    {
      break;
    }
    else
    {
      swap(arr[low], arr[largeIndex]);
      low = largeIndex;
      largeIndex = 2 * low + 1;
    }
  }
}

void buildHeap(int *arr, int size)
{
  for (int i = size / 2 - 1; i > -1; i--)
  {
    heapify(arr, i, size - 1);
    // print(arr, size);
    // cout<<endl;
  }
}

void heapSort(int *arr, int size)
{
  buildHeap(arr, size);
  for (int i = size - 1; i >= 0; i--)
  {
    swap(arr[i], arr[0]);
    print(arr, size);
    heapify(arr, 0, i - 1);
    // print(arr, size);
    // cout<<endl;
  }
}

void shellSort(int *arr, int size)
{
  for (int i = size / 2; i > 0; i /= 2)
  {
    for (int j = i; j < size; j++)
    {
      int temp = arr[j];
      int r;
      for (r = j; r >= i && arr[r - i] > temp; r -= i)
      {
        arr[r] = arr[r - i];
      }
      arr[r] = temp;
    }
  }
}

int main()
{
  int arr[] = {40, 1, 12, 5, 3, 6, 3, 0, 2};
  int length = 9;
  cout << "Unsorted : ";
  print(arr, length);
  // shellSort(arr, 9);
  // bucketSort(arr,9);
  quickSort(arr, 0, 9);
  // cout << "Shell sort: " << endl;
  // cout << "Bucket sort: " << endl;
  cout << "Quick sort: " << endl;
  print(arr, length);
}