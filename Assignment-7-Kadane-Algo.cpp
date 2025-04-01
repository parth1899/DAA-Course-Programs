// Largest Contiguos Block Sum 
// 1. Brute Force
// 2. Kadane Algorithm

#include <iostream>
#include <vector>
using namespace std;

int brute(vector<int>& arr) {
    int result = INT_MIN;
    int curr = 0;
    
    for(int i = 0; i < arr.size(); i++) {\
        for(int j = 1; j < arr.size() - i; j++) {
            // j is the window size
            for(int k = i; k < i + j; k++) {
                curr += arr[k];
            }
            result = max(curr, result);
            curr = 0;
            // curr += arr[j];
        }        
    }

    return result;
}

int brute2(vector<int>& arr) {
    int result = INT_MIN;
    for(int i = 0; i < arr.size(); i++) {
        int curr = arr[i];
        for(int j = i + 1; j < arr.size(); j++) {
            curr += arr[j];
            result = max(result, curr);
        }
    }
    return result;
}

int kadane(vector<int>& arr) {
    int result = INT_MIN;
    int curr = 0;
    for(int& i : arr) {
        curr += i;
        if(curr < 0) {
            curr = 0;
        }
        result = max(result, curr);
    }
    return result;
}

int main() {    
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << brute(arr) << endl;
    cout << brute2(arr) << endl;
    cout << kadane(arr) << endl; 
}