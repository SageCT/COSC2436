#include <iostream>
#include <random>
using namespace std;

void print(int arr[], int size) {
  for (int i = 0; i < size; i++) cout << arr[i] << " ";
  cout << endl;
}

void merge(int arr[], int low, int mid, int high) {
  int l = low;       // Starting index for left subarray
  int r = mid + 1;   // Starting index for temporary array
  int mergePos = 0;  // Starting index for right subarray

  int arrSize = (high - low) + 1;
  int *temp = new int[arrSize];

  while (l <= mid && r <= high) {
    // arr[i] is smaller than arr[j]
    if (arr[l] < arr[r]) {
      temp[mergePos] = arr[l];
      l++;
    } else {
      temp[mergePos] = arr[r];  // arr[j] is smaller than arr[i]
      r++;
    }

    mergePos++;
  }

  // Copying all elements from the left subarray to temp as it is
  while (l <= mid) {
    temp[mergePos] = arr[l];
    mergePos++, l++;
  }
  // Copying all elements from the right subarray to temp as it is
  while (r <= high) {
    temp[mergePos] = arr[r];
    mergePos++, r++;
  }

  for (int x = low; x < arrSize; x++) 
    arr[x] = temp[x];
    
  
  delete[] temp;
}

void mergeSort(int *arr, int low, int high) {
  if (low < high) {
    int mid = low + (high - low) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);

    merge(arr, low, mid, high);
  }
}

void quickSort() {}

void shellSort() {}

int main() {
  int arr[10];
  for (int x = 0; x < 10; x++) {
    arr[x] = rand() % 100;
    cout << arr[x] << " ";
  }
  cout << endl;

  mergeSort(arr, 0, 9);

  for (int x = 0; x < 10; x++) {
    cout << arr[x] << " ";
  }
  cout << endl;

  return 0;
}