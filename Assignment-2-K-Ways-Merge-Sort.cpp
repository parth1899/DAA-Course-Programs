#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;


vector<int> mergeParts(vector<int>& arr, int k, int part_size, int low, int high) {
    
    auto customCompare = [&arr](int a, int b) {
        return arr[a] > arr[b]; 
    };
    priority_queue<int, vector<int>, decltype(customCompare)> pq(customCompare);

    // Push the starting indices of all k parts into the heap
    for (int i = 0; i < k; i++) {
        int startIdx = low + i * part_size;
        if (startIdx < high) {
            pq.push(startIdx);
        }
    }

    vector<int> tempSorted;
    tempSorted.reserve(high - low);

    // Merge
    while (!pq.empty()) {
        int topIndex = pq.top();
        pq.pop();

        tempSorted.push_back(arr[topIndex]);
        int nextIdx = topIndex + 1;

        // Check if the next index is within the same part and within bounds
        if (nextIdx < low + ((topIndex - low) / part_size + 1) * part_size && nextIdx < high) {
            pq.push(nextIdx);
        }
    }

    return tempSorted;
}

void mergeSort(vector<int>& arr, int k, int low, int high) {
    
    int length = high - low;
    // if (length <= 1) {
    //     // Nothing to sort if subarray has 0 or 1 element
    //     // return vector<int>(arr.begin() + low, arr.begin() + high);
    //     return;
    // }

    int part_size = static_cast<int>(ceil((double)length / k));

    //small case
    if (part_size < k) {
        sort(arr.begin() + low, arr.begin() + high);
        // return vector<int>(arr.begin() + low, arr.begin() + high);
        return;
    }

    // solve for k parts
    for (int i = 0; i < k; i++) {
        int start = low + i * part_size;
        if (start >= high) {
            break; 
        }
        int end = min(start + part_size, high);
        mergeSort(arr, k, start, end);
    }

    // merge all k sorted parts in the range [low, high) into one sorted segment
    vector<int> merged = mergeParts(arr, k, part_size, low, high);

    // copy the merged result back into arr
    for (int i = 0; i < (int)merged.size(); i++) {
        arr[low + i] = merged[i];
    }

    // return merged;
}

int main() {
    vector<int> arr;
    int n, k;

    cout << "Enter the size of the array: ";
    cin >> n;
    cout << "Enter the number of parts (k): ";
    cin >> k;

    cout << "Enter the elements of the array: ";
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Perform k-way merge sort
    mergeSort(arr, k, 0, n);

    // Print the final sorted array
    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}