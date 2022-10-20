//This program contains the code for heap sort, quick sort, merge sort, and shell sort.
#include<iostream>
using namespace std;

void print(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void heapify(int arr[], int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if(l < n && arr[l] > arr[largest]){
        largest = l;
    }

    if(r < n && arr[r] > arr[largest]){
        largest = r;
    }

    if(largest != i){
        int temp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n){
    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }

    for(int i = n - 1; i > 0; i--){
        int temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;

        heapify(arr, i, 0);
    }
}

void merge(int arr[], int i, int j, int k){
    int mergeSize = k - i + 1;
    int mergePos = 0;
    int l = i;
    int r = j+1;
    int *nArr = new int[mergeSize];
    while(l <= j && r <= k){
        if(arr[l] < arr[r]){
            nArr[mergePos] = arr[l];
            l++;
        }
        else{
            nArr[mergePos] = arr[r];
            r++;
        }
        mergePos++;
    }
    while(l <= j){
        nArr[mergePos] = arr[l];
        mergePos++;
        l++;
    }
    while(r <= k){
        nArr[mergePos] = arr[r];
        mergePos++;
        r++;
    }
    for(mergePos = 0; mergePos < mergeSize; mergePos++){
        arr[mergePos + i] = nArr[mergePos];
    }
    delete [] nArr;
}

void mergeSort(int arr[], int i, int k){
    if(i < k){
        int j = i + (k - i) / 2;
        mergeSort(arr, i , j);
        mergeSort(arr, j + 1, k);
        merge(arr, i , j, k);
    }
}

int partition(int arr[], int i, int k){
    int midpoint = i + (k - i) / 2;
    int pivot = arr[midpoint];
    int l = i;
    int h = k;
    bool done = false;
    while(!done){
        while(arr[l] < pivot){
            l++;
        }
        while(pivot < arr[h]){
            h--;
        }
        if(l >= h){
            done = true;
        }
        else{
            int temp = arr[l];
            arr[l] = arr[h];
            arr[h] = temp;
            l++;
            h--;
        }
    }
    return h;
}
void quickSort(int arr[], int i, int k){
    if(i < k){
        int j = partition(arr, i, k);
        quickSort(arr, i, j);
        quickSort(arr, j+1, k);
    }
}

void shellSort(int arr[], int size){
    for(int gap = size / 2; gap > 0; gap /= 2){
        for(int i = gap; i < size; i += 1){
            int temp = arr[i];
            int j;
            for(j = i; j >= gap && arr[j-gap] > temp; j -= gap)
                arr[j] = arr[j-gap];
            arr[j] = temp;
        }
    }
}

int main(){

    int size = 0;
    cout << "Enter Size of Array: ";
    cin >> size;
    int *arr = new int[size];

    int number = 0;
    cout << "Enter " << size << " numbers to put into the array." << endl;
    for(int i = 0; i < size; i++){
        cin >> number;
        arr[i] = number;
    }

    cout << "Menu:\n1) Heap Sort\n2) Quick Sort\n3) Merge Sort\n4) Shell Sort\n5) Exit" << endl;
    int choice = 0;
    cin >> choice;
    while(choice != 5){
        if(choice == 1){
            heapSort(arr, size);
            cout << "Array sorted using heap sort." << endl;
            print(arr, size);
        }
        else if(choice == 2){
            cout << "Array sorted using quick sort." << endl;
            quickSort(arr, 0, size - 1);
            print(arr, size);
        }
        else if(choice == 3){
            cout << "Array sorted using merge sort." << endl;
            mergeSort(arr, 0, size);
            print(arr, size);
        }
        else if(choice == 4){
            cout << "Array sorted using shell sort" << endl;
            shellSort(arr, size);
            print(arr, size);
        }
        else{
            cout << "Invalid Choice" << endl;
        }
        cin >> choice;
    }

    delete [] arr;

    return 0;
}