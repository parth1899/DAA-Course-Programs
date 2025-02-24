// Majority Searching Element
// 1. Brute Force
// 2. Sorting
// 2. Boyer-Moore Majority Voting Algorithm

// Majority: A given number is majority if it occurs more than n/2 times


#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int hashMap(vector<int>& arr) {
    unordered_map<int, int> m;
    for(int& num : arr) m[num]++;

    int maxE = INT_MIN; // get the most occurences;
    int element;

    for(auto it : m) {
        if(it.second > maxE) {
            maxE = it.second;
            element = it.first;
        }
    }

    return element;
}

int brute(vector<int>& arr) {
    int n = arr.size();

    for(int i = 0; i < arr.size(); i++) {
        int count = 0;
        for(int j = 0; j < arr.size(); j++) {
            if(arr[i] == arr[j]) {
                count++;
            }
        }
        if(count > n/2) return arr[i];
    }
    return -1;
}

int sorting(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    int n = arr.size();
    int counter = 0;
    int element = -1;

    for(int i = 0; i < arr.size(); i++) {
        if(element == arr[i]) {
            counter++;
            if(counter > n/2) return element;
        }
        else {
            element = arr[i];
            counter = 1;
        }
    }

    return -1;
}

int boyerMoore(vector<int> arr) {
    int candidate = -1;
    int votes = 0;

    for(int i = 0; i < arr.size(); i++) {
        if(votes == 0) {
            candidate = arr[i];
            votes = 1;
        }
        else {
            if(arr[i] == candidate) {
                votes++;
            }
            else {
                votes--;
            }
        }
    }

    // now check if the candidate is majority
    int count = 0;
    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] == candidate) count++;
    }
    if(count > arr.size() / 2) return candidate;
    return -1;
}

int main() {
    vector<int> arr;
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the elements one by one" << endl;
    
    int t = n;
    while(t--) {
        int temp;
        cin >> temp;
        arr.push_back(temp);
    }

    int result = brute(arr);
    (result == -1) ? cout << "No majority element found" : cout << "The majority element using Brute Force is: " << result << endl;
    
    int result2 = sorting(arr);
    (result2 == -1) ? cout << "No majority element found using sorting method" : cout << "The majority element using Sorting method is: " << result2 << endl;

    int result3 = boyerMoore(arr);
    (result3 == -1) ? cout << "No majority element found using the boyer Moore method" : cout << "The majority element using Boyer Moore voting algorithm is: " << result3;
}