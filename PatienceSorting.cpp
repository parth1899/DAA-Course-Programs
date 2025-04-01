// Patience Sorting

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> patienceSorting(const vector<int>& sequence) {
    vector<vector<pair<int, int>>> decks; // Stores (value, previous index)
    vector<pair<int, int>> last_indices; // Stores last element of each deck with its original index

    for (int i = 0; i < sequence.size(); i++) {
        int num = sequence[i];

        // Find the first deck where num can be placed using binary search
        auto it = lower_bound(last_indices.begin(), last_indices.end(), make_pair(num, 0));

        int deckIndex = it - last_indices.begin();
        int prevIndex = (deckIndex == 0) ? -1 : decks[deckIndex - 1].back().second;

        if (deckIndex < decks.size()) {
            // Replace the last element in the existing deck
            decks[deckIndex].push_back({num, prevIndex});
            last_indices[deckIndex] = {num, i};
        } else {
            // Create a new deck
            decks.push_back({{num, prevIndex}});
            last_indices.push_back({num, i});
        }
    }

    // Reconstruct the Longest Increasing Subsequence (LIS)
    vector<int> lis;
    int lastIndex = decks.back().back().second;
    
    for (int i = decks.size() - 1; i >= 0; i--) {
        for (auto it = decks[i].rbegin(); it != decks[i].rend(); ++it) {
            if (it->second == lastIndex || lastIndex == -1) {
                lis.push_back(it->first);
                lastIndex = it->second;
                break;
            }
        }
    }

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