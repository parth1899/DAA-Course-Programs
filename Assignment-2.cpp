// Quick Sort (normal) and Merge Sort (k-way)
// Name: Parth Kalani

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

// Quick Sort Implementation
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for(int j = low; j < high; j++) {
        if(arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// K-way Merge Sort Implementation
// Structure for queue elements
struct QueueNode {
    int value;      // Value of the element
    int arrayIndex; // Index of array from which element came
    int nextIndex;  // Index of next element in the array
    
    QueueNode(int v, int aIndex, int nIndex) 
        : value(v), arrayIndex(aIndex), nextIndex(nIndex) {}
};

// Custom comparator for min-heap
struct CompareNode {
    bool operator()(const QueueNode& n1, const QueueNode& n2) {
        return n1.value > n2.value;
    }
};

// K-way merge function
vector<int> kWayMerge(vector<vector<int>>& arrays, int k) {
    vector<int> result;
    
    // Create a min heap
    priority_queue<QueueNode, vector<QueueNode>, CompareNode> minHeap;
    
    // Push first element from each array
    for(int i = 0; i < k; i++) {
        if(!arrays[i].empty()) {
            minHeap.push(QueueNode(arrays[i][0], i, 1));
        }
    }
    
    // Keep popping minimum element and pushing next element from same array
    while(!minHeap.empty()) {
        QueueNode curr = minHeap.top();
        minHeap.pop();
        
        result.push_back(curr.value);
        
        // If there are more elements in the array, push the next element
        if(curr.nextIndex < arrays[curr.arrayIndex].size()) {
            minHeap.push(QueueNode(
                arrays[curr.arrayIndex][curr.nextIndex],
                curr.arrayIndex,
                curr.nextIndex + 1
            ));
        }
    }
    
    return result;
}

// Function to split array into k parts for k-way merge sort
vector<vector<int>> splitArray(const vector<int>& arr, int k) {
    vector<vector<int>> result(k);
    int size = arr.size();
    int baseSize = size / k;
    int extra = size % k;
    
    int current = 0;
    for(int i = 0; i < k; i++) {
        int partSize = baseSize + (extra > 0 ? 1 : 0);
        extra--;
        
        for(int j = 0; j < partSize && current < size; j++) {
            result[i].push_back(arr[current++]);
        }
        
        // Sort this partition using quick sort
        if(!result[i].empty()) {
            quickSort(result[i], 0, result[i].size() - 1);
        }
    }
    
    return result;
}

// K-way Merge Sort main function
vector<int> kWayMergeSort(vector<int>& arr, int k) {
    // If k is greater than array size, adjust k
    k = min(k, (int)arr.size());
    
    // Split array into k parts and sort each part
    vector<vector<int>> parts = splitArray(arr, k);
    
    // Merge k sorted arrays
    return kWayMerge(parts, k);
}

// Utility function to print array
void printArray(const vector<int>& arr) {
    for(int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    int n, k;
    cout << "Enter the number of elements: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "Enter k for k-way merge sort (k > 1): ";
    cin >> k;
    
    // Make a copy for quick sort
    vector<int> arr_quick = arr;
    
    cout << "\nOriginal array: ";
    printArray(arr);
    
    // Quick Sort
    quickSort(arr_quick, 0, n-1);
    cout << "After Quick Sort: ";
    printArray(arr_quick);
    
    // K-way Merge Sort
    vector<int> arr_merged = kWayMergeSort(arr, k);
    cout << "After " << k << "-way Merge Sort: ";
    printArray(arr_merged);
    
    return 0;
}
