// Disjoint Set Union

// Three main functions:
// 1. Make : Adds a new independent node
// 2. Find : returns the parent of the group for a given node
// 3. Union : Adds two nodes a and b to the same group (basically merges two groups)

#include <iostream>
using namespace std;
const int N = 1000;

int parent[N];
int sz[N]; // stores the size of the given group

void make(int v) {
    parent[v] = v; // independent node
    sz[v] = 1;
}

int find(int a) {
    if(parent[a] == a) return a;
    return find(parent[a]);
}

int Union(int a, int b) {
    int a = parent[a];
    int b = parent[b]; 

    if(a != b) {
        // always have the bigger tree on the left, join the smaller tree (on the right) with the bigger tree.
        if(sz[a] < sz[b]) {
            swap(a, b);
        }
        parent[b] = a;
        sz[a] += sz[b];
    }
}

int main() {
    make(1);
    make(2);
    make(3);
    make(4);

}