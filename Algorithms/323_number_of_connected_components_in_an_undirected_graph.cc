/*
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to find the number of connected components in an undirected graph.

Example 1:
     0          3
     |          |
     1 --- 2    4
Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.

Example 2:
     0           4
     |           |
     1 --- 2 --- 3
Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.

Note:
You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.
*/

// Solution using DFS on a birectional graph.
class Graph {
public:
    Graph(int _V) : V(_V) {
        adj.resize(V);
        visited.resize(V);
    }
    
    void addEdge(int i, int j) {
        adj[i].push_back(j);
        adj[j].push_back(i);
    }

    int numComponents() {
        int nc = 0;
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                dfs(i);
                nc ++;
            }
        }
        return nc;
    }

    void dfs(int i) {
        visited[i] = true;
        for (const int j : adj[i]) {
            if (!visited[j]) dfs(j);
        }
    }
    
private:
    int V;
    vector<vector<int>> adj;    
    vector<bool> visited;
};

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        Graph g(n);
        for (const auto &edge : edges) {
            g.addEdge(edge[0], edge[1]);
        }
        return g.numComponents();
    }
};

// Solution using union find (weighted quick union with path compression by halving)
class UnionFind {
public:
    UnionFind(int nn): n(nn) {
        id.resize(nn);
        size.resize(nn, 1);
        for(int i = 0; i < nn; i++) {
            id[i] = i;
        }
    }
    void unite(int i, int j) {
        while(id[i] != i) { id[i] = id[id[i]]; i = id[i]; }
        while(id[j] != j) { id[j] = id[id[j]]; j = id[j]; }
        if(i == j) return; //already connected
        if(size[i] < size[j]) { id[i] = j; size[j] += size[i]; }
        else { id[j] = i; size[i] += size[j]; }
        n--;
    }
    int count() const { return n; }

private:
    vector<int> id, size;
    int n;
};

class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        if(n == 0) return 0;
        UnionFind uf(n);
        for (auto e : edges)
            uf.unite(e.first, e.second);
        
        return uf.count();
    }
};
