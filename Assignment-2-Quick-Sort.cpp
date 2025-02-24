#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

// Quick Sort Implementation
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low]; //first element
    int i = low;
    int j = high;
    
    while(i < j) {
        while(arr[i] <= pivot && i <= high - 1) {
            i++;
            //find the first element from the left greater than pivot
        }
        while(arr[j] > pivot && j >= low + 1) {
            j--;
            //find the first element from the right smaller than pivot
        }
        if(i < j) swap(arr[i], arr[j]);
    }

    swap(arr[low], arr[j]);
    return j;
}

void quickSort(vector<int>& arr, int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(const vector<int>& arr) {
    for(int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "\nOriginal array: ";
    printArray(arr);
    
    // Quick Sort
    quickSort(arr, 0, n-1);
    cout << "After Quick Sort: ";
    printArray(arr);
        
    return 0;
}
