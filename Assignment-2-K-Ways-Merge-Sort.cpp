#include <iostream>
#include <vector>
#include <queue>
#include <cmath> // for ceil
#include <algorithm> // for sort

using namespace std;

// Function to merge k sorted parts using a priority queue
vector<int> merge(const vector<vector<int>>& sortedParts) {
    auto customCompare = [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first > b.first;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(customCompare)> pq(customCompare);

    // Initialize the priority queue with the first element of each part
    for (int i = 0; i < sortedParts.size(); i++) {
        if (!sortedParts[i].empty()) {
            pq.push({sortedParts[i][0], i});
        }
    }

    vector<int> mergedArray;
    vector<int> pointers(sortedParts.size(), 0); // Track the current index in each part

    while (!pq.empty()) {
        auto [value, partIdx] = pq.top();
        pq.pop();

        mergedArray.push_back(value);

        // Move the pointer in the current part and push the next element into the queue
        if (++pointers[partIdx] < sortedParts[partIdx].size()) {
            pq.push({sortedParts[partIdx][pointers[partIdx]], partIdx});
        }
    }

    return mergedArray;
}

// Function to perform k-way merge sort
vector<int> mergeSort(const vector<int>& arr, int k, int low, int high) {
    if (high - low <= 1) {
        return vector<int>(arr.begin() + low, arr.begin() + high);
    }

    int part_size = ceil((double)(high - low) / k);
    vector<vector<int>> sortedParts;

    // Divide the array into k parts and sort each part recursively
    for (int i = 0; i < k; i++) {
        int start = low + i * part_size;
        int end = min(start + part_size, high);

        if (start < high) {
            vector<int> sortedPart = mergeSort(arr, k, start, end);
            sortedParts.push_back(sortedPart);
        }
    }

    // Merge the k sorted parts
    return merge(sortedParts);
}

int main() {
    vector<int> arr;
    int n, k;

    // Input array size and number of parts
    cout << "Enter the size of the array: ";
    cin >> n;
    cout << "Enter the number of parts (k): ";
    cin >> k;

    // Validate input
    if (n <= 0 || k <= 0) {
        cout << "Invalid input. Size and k must be positive integers." << endl;
        return 1;
    }

    if (k > n) {
        cout << "Warning: k is larger than the array size. Setting k to " << n << "." << endl;
        k = n;
    }

    // Input the array elements
    cout << "Enter the elements of the array: ";
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Perform K-way merge sort
    vector<int> sortedArray = mergeSort(arr, k, 0, n);

    // Output the sorted array
    cout << "Sorted array: ";
    for (int num : sortedArray) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}