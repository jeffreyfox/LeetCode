/*
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

For example:

Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.

Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.

Hint:

    Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], what should your return? Is this case a valid tree?
    According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”

Note: you can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges. 
*/

// Solution 1. Union find with weighted quick-union and path compression by halving. For a graph to be a tree, it has to make sure:
// no cycles
// no disconnected components
class UnionFind {
public:
    UnionFind(int N) : n(N) {
        id.resize(N, 0);
        for(int i = 0; i < N; ++i) id[i] = i;
        size.resize(N, 1);
    }
    bool unite(int i, int j) {
        while(id[i] != i) { id[i] = id[id[i]]; i = id[i]; }
        while(id[j] != j) { id[j] = id[id[j]]; j = id[j]; }
        if(i != j) {
            if(size[i] < size[j]) { id[i] = j; size[j] += size[i]; }
            else { id[j] = i; size[i] += size[j]; }
            n--;
            return true;
        } else return false; //already connected
    }
    int count() const { return n; }

private:
    vector<int> id;
    vector<int> size;
    int n;
};

class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
         UnionFind uf(n);
         for(auto it : edges)
             if(!uf.unite(it.first, it.second)) return false;
         return uf.count() == 1;
    }
};

// Solution 2 using DFS cycle detection
class Graph {
public:
    Graph(int n) : N(n) {
       adj.resize(n);
    }
    int NV() const { return N; }
    void addEdge(int i, int j) {
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    int N;
    vector<vector<int> > adj; //adjacency list
};

class GraphValidTree {
public:
    GraphValidTree(const Graph& graph) : g(graph) {
        int nv = g.NV();
        state.resize(nv, 0);
    }
    bool isValidTree() {
        if(!dfs(0, -1)) return false;
        // check if there are still unvisited nodes (g is a forest)
        for(int i = 0; i < g.NV(); ++i) {
            if(state[i] == 0) return false;
        }
        return true;
    }
    bool dfs(int v, int p) {
        state[v] = 1;
        for(int w : g.adj[v]) {
            if(w == p) continue; //its parent
            if(state[w] != 0 || !dfs(w, v)) return false;
        }
        return true;
    }
    const Graph& g;
    vector<int> state;
};

class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
         if(n == 0) return true;
         Graph g(n);
         for(auto it : edges)
             g.addEdge(it.first, it.second);

         GraphValidTree gvt(g);
         return gvt.isValidTree();
    }
};

