/*
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:

2, [[1,0]]

There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.

2, [[1,0],[0,1]]

There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.

click to show more hints.
Hints:

    This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
    Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
    Topological sort could also be done via BFS.
*/

// 2022. Solution using DFS cycle detection
// Note: We need to run DFS on all nodes because there could be several partitions in the graph.

class Graph {
public:
    Graph(int _V) : V(_V), has_cycle(false) {
        adj.resize(V);
        visited.resize(V, false);
        on_stack.resize(V, false);
    }
    void addEdge(int v, int w) { adj[v].push_back(w); }
    bool detectCycle() {
        for (int v = 0; v < V; ++v) {
            if (!visited[v]) dfs(v);
        }
        return has_cycle;
    }

    void dfs(int v) {
        if (has_cycle) return;
        if (visited[v]) return;
        visited[v] = true;
        on_stack[v] = true;
        for (const int w : adj[v]) {
            if (on_stack[w]) {
                has_cycle = true;
                return;
            }
            if (!visited[w]) {
                dfs(w);
            }
        }
        on_stack[v] = false;        
    }
    bool hasCycle() { return has_cycle; }
    
private:
    int V;
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<bool> on_stack;
    bool has_cycle;
};

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        Graph g(numCourses);
        for (const auto &pre : prerequisites) {
            g.addEdge(pre[1], pre[0]);
        }
        return !g.detectCycle();        
    }
};

// 2015. Solution using graph cycle-detection using dfs

class Graph {
public:
    Graph(int NN) : N(NN) {
        adj.resize(N);
    }
    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }
    int NV() const { return N; }
    const vector<int>& neighbors(int v) const { return adj[v]; }
private:
    int N; //number of vertices
    vector<vector<int> > adj; //adjacency lists
};

class CycleDetector {
public:
    CycleDetector(const Graph& gg): g(gg), hasCycle(false) {
        status.resize(g.NV(), 0);
    }
    //detect cycle using dfs, immediately return if found cycle
    bool detectCycle() { 
        for(int v = 0; v < g.NV() && !hasCycle; v++) {
            if(status[v] == 0) dfs(v);
        }
        return hasCycle;
    }
private:
    void dfs(int v) {
        status[v] = 1; //on stack
        for(auto w : g.neighbors(v)) {
            if(hasCycle) return; //found cycle, just return
            if(status[w] == 1) { hasCycle = true; return; } //found cycle!
            else if(status[w] == 0) dfs(w); //unvisited, visit
        }
        status[v] = 2; //finished
    }
    const Graph& g;
    bool hasCycle; //has cycle
    vector<int> status; //vertex status during dfs (0: unvisited, 1: onstack, 2: finished)
};

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        //construct directed graph
        Graph g(numCourses);
        for(auto c : prerequisites) 
            g.addEdge(c.second, c.first);
        //detect cycle using dfs
        CycleDetector det(g);
        return !det.detectCycle();
    }
};

