#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <string>

using namespace std;

void print(int arr[], int size) {
  for (int i = 0; i < size; i++) cout << arr[i] << " ";
  cout << endl;
}

bool isSorted(int *arr, int size) {
  for (int i = 0; i < size - 1; i++)
    if (arr[i] > arr[i + 1]) return false;
  return true;
}

void insertionSort(int *arr, int size) {
  for (int i = 1; i < size; i++) {
    int j = i;
    while (j > 0 && arr[j - 1] > arr[j]) {
      swap(arr[j], arr[j - 1]);
      j--;
    }
  }
}

void merge(int *arr, int low, int mid, int high) {
  int l = low;       // Starting index for left subarray
  int r = mid + 1;   // Starting index for temporary array
  int mergePos = 0;  // Starting index for right subarray

  int arrSize = (high - low) + 1;
  int *temp = new int[arrSize];

  while (l <= mid && r <= high) {
    // arr[i] is smaller than arr[j]
    if (arr[l] <= arr[r]) {
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

int partition(int *arr, int left, int right) {
  int partIndex = left;
  int pivot = arr[right];
  int l = left;
  int r = right;
  // Compares pivot to the array at index, if the pivot is bigger than index,
  // swap right index with curr index
  for (int i = left; i < right; i++) {
    if (pivot >= arr[i]) {
      swap(arr[partIndex], arr[i]);  // Important fuct
      partIndex++;
    }
  }
  // Swap pivot with the element at partIndex
  swap(arr[partIndex], arr[right]);
  return partIndex;
}

void quickSort(int *arr, int left, int right) {
  if (left < right) {
    int pivot = partition(arr, left, right);
    quickSort(arr, left, pivot - 1);
    quickSort(arr, pivot + 1, right);
  }
}

void bucketSort(int *arr, int n) {
  // create n empty buckets
  vector<int> *buckets = new vector<int>[n];
  for (int x = 0; x < n; x++) {
    if (arr[x] > n) {
      buckets[n - 1].push_back(arr[x]);
    } else {
      buckets[arr[x]].push_back(arr[x]);
    }
  }
  // Sorting individual buckets
  for (int x = 0; x < n; x++) sort(buckets[x].begin(), buckets[x].end());

  // Adding sorted buckets back to the array
  int index = 0;
  for (int x = 0; x < n; x++)
    for (int y = 0; y < buckets[x].size(); y++) arr[index++] = buckets[x][y];
}

int findMax(int *arr, int length) {
  int max = arr[0];
  for (int i = 1; i < length; i++)
    if (max < arr[i]) max = arr[i];

  return max;
}

void radixSort(int *arr, int n) {}

void heapify(int *arr, int i, int size) {
  int leftC = 2 * i + 1;
  int rightC = 2 * i + 2;
  int largest = i;

  // If left child INDEX is larger than root value,
  // new largest index is leftC
  if (leftC < size && arr[leftC] > arr[i]) largest = leftC;

  // If right child INDEX is larger than root value, or iteration
  if (rightC < size && arr[rightC] > arr[largest]) largest = rightC;

  // If largest is not the root
  if (largest != i) {
    swap(arr[i], arr[largest]);
    heapify(arr, largest, size);
  }
}

void buildHeap(int *arr, int size) {
  for (int i = size / 2 - 1; i > -1; i--) {
    heapify(arr, i, size - 1);
  }
}

bool isHeap(int *arr, int size) {
  for (int i = 0; i < size / 2 - 1; i++) {
    if (arr[i] < arr[2 * i + 1] || arr[i] < arr[2 * i + 2]) return false;
  }
  return true;
}

void heapSort(int *arr, int size) { buildHeap(arr, size); }

void shellSort(int *arr) {}

int main() {
  int arr[10];

  cout << "Before sort: \n";
  for (int x = 0; x < 10; x++) {
    arr[x] = rand() % 100;
    cout << arr[x] << " ";
  }
  cout << "\n\n";

  // heapSort(arr, 10);
  buildHeap(arr, 10);
  // insertionSort(arr, 10);
  // mergeSort(arr, 0, 9);
  // quickSort(arr, 0, 9);
  // bucketSort(arr, 9);
  // heapSort(arr, 0, 9);
  // radixSort(arr, 0 ,9);

  cout << "After building heap: " << endl;
  // cout << "After insertionSort: " << endl;
  // cout << "After mergeSort: " << endl;
  // cout << "After quickSort: " << endl;
  // cout << "After bucketSort: " << endl;
  // cout << "After heapSort: " << endl;
  // cout << "After radixSort: " << endl;

  for (int x = 0; x < 10; x++) {
    cout << arr[x] << " ";
  }

  cout << "\n"
       << "Sorted?: ";
  (isSorted(arr, 10)) ? cout << "Yes" << endl : cout << "No" << endl;

  cout << "Heapified?: ";
  (isHeap(arr, 10)) ? cout << "Yes" << endl : cout << "No" << endl;

  return 0;
}