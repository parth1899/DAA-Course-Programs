#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> patienceSorting(const vector<int>& sequence) {
    vector<vector<int>> piles;  // Each pile will store values in decreasing order
    vector<int> pile_tops;      // Keeps track of the top card of each pile
    vector<int> predecessor(sequence.size(), -1);  // Stores indices of predecessors
    vector<int> pile_idx(sequence.size(), -1);     // Stores which pile each element belongs to
    
    // Create piles (patience sorting algorithm)
    for (int i = 0; i < sequence.size(); i++) {
        int num = sequence[i];
        
        // Find the leftmost pile whose top card is greater than or equal to num
        auto it = lower_bound(pile_tops.begin(), pile_tops.end(), num);
        int pile = it - pile_tops.begin();
        
        // Record which pile this card is placed on
        pile_idx[i] = pile;
        
        // Set the predecessor for this element
        if (pile > 0) {
            // Find the index of the top card in the previous pile
            int prev_pile_top_idx = -1; 
            for (int j = i - 1; j >= 0; j--) {
                if (pile_idx[j] == pile - 1 && sequence[j] < num) {
                    prev_pile_top_idx = j;
                    break;
                }
            }
            predecessor[i] = prev_pile_top_idx;
        }
        
        // Add to existing pile or create a new one
        if (pile == piles.size()) {
            piles.push_back({num});
            pile_tops.push_back(num);
        } else {
            piles[pile].push_back(num);
            pile_tops[pile] = num;
        }
    }
    
    // Reconstruct LIS
    vector<int> lis;
    if (piles.empty()) return lis;
    
    // Start with the index of the top card in the rightmost pile
    int curr_idx = -1;
    int max_pile = piles.size() - 1;
    
    for (int i = sequence.size() - 1; i >= 0; i--) {
        if (pile_idx[i] == max_pile) {
            curr_idx = i;
            break;
        }
    }
    
    // Follow predecessors to reconstruct the full sequence
    while (curr_idx != -1) {
        lis.push_back(sequence[curr_idx]);
        curr_idx = predecessor[curr_idx];
    }
    
    // Reverse to get increasing order
    reverse(lis.begin(), lis.end());
    return lis;
}

int main() {
    // int n;
    // cout << "Enter the number of elements: ";
    // cin >> n;
    // vector<int> arr(n);
    // cout << "Enter sequence of integers: ";
    // for (int i = 0; i < n; i++) {
    //     cin >> arr[i];
    // }
    vector<int> arr = {6, 3, 5, 10, 11, 2, 9, 14, 13, 7, 4, 8, 12};
    vector<int> longestIncreasingSubsequence = patienceSorting(arr);
    cout << "Longest Increasing Subsequence: ";
    for (int num : longestIncreasingSubsequence) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}