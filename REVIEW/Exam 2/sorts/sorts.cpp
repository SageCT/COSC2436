#include <iostream>
#include <random>
using namespace std;

void print(int arr[], int size) {
  for (int i = 0; i < size; i++) cout << arr[i] << " ";
  cout << endl;
}

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
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

  for (int x = low; x < arrSize; x++) arr[x] = temp[x];

  delete[] temp;
}

// Mergesort INFO
// Time Complexity: O[nlog(n)]
// Drawbacks: High memory usage, Copying time

void mergeSort(int *arr, int low, int high) {
  if (low < high) {
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);

    merge(arr, low, mid, high);
  }
}

int partition(int arr[], int left, int right) {
  int partIndex = left;
  int pivot = arr[right];
  int l = left;
  int r = right;

  for (int i = left; i < right; i++) {
    if (pivot >= arr[i]) {
      swap(arr[partIndex], arr[i]);
      partIndex++;
    }
  }

  int temp = arr[partIndex];
  arr[partIndex] = arr[right];
  arr[right] = temp;
}

void quickSort(int arr[], int left, int right) {
  if (left < right) {
    int pivot = partition(arr, left, right);
    quickSort(arr, left, pivot - 1);
    quickSort(arr, pivot + 1, right);
  }
}

void shellSort(int arr[]) {}

void bucketSort(int arr[]) {}

void radixSort(int arr[]) {}

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