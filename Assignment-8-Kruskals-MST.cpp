// Greedy Algorithm - Kruskal's Algorithm for Minimum Spanning Tree

// If an undirected weighted graph has n vertices, the MST will have (n-1) edges

// Algorithm:
// 1. Pick the smallest weighted edge. (Greedy)
// 2. If it doesnt form a cycle with the existing MST, include it in the MST
// 3. Repeat 1 and 2 until we have (n-1) edges in the MST

#include <iostream>
#include <vector>
#include <algorithm>
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

void Union(int a, int b) {
    a = parent[a];
    b = parent[b]; 

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

    int n, e; // nodes and edges
    cout << "Enter the number of nodes and number of edges: ";
    cin >> n >> e;
    vector<pair<int, pair<int, int>>> edges; // weight, u, v
    
    for(int i = 0; i < e; i++) {
        cout << "Enter edge (start, end, weight)" << i + 1 << ": ";
        int u, v, wt;
        cin >> u >> v >> wt;
        edges.push_back({wt, {u, v}});
    }    

    // sort, in pair when we sort it considers the first member
    sort(edges.begin(), edges.end()); // Greedy step

    // make the nodes
    for(int i = 1; i <= n; i++) {
        make(i);
    }

    // now check whether for the given edge, for each node their parent is same or not. 
    // if yes, that edge will form a cycle

    int cost = 0;

    cout << "The MST will have these nodes: " << endl;

    for(auto edge : edges) {
        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        

        if(find(u) == find(v)) continue; // dont add this edge
        Union(u, v); // combine the sets
        cost += wt;

        cout << u << " " << v << " " << wt << endl;
    }

    cout << "The total weight of the MST is: " << cost << endl;


    return 0;
}