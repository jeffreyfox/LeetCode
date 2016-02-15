/*
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

For example:

2, [[1,0]]

There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]

There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.

click to show more hints.
Hints:

    This problem is equivalent to finding the topological order in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
    Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
    Topological sort could also be done via BFS.
*/

// Solution using topological sort with dfs

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

class TopoSort {
public:
    TopoSort(const Graph& gg): g(gg), hasCycle(false) {
        status.resize(g.NV(), 0);
    }
    //detect cycle using dfs, immediately return if found cycle
    void sort() { 
        for(int v = 0; v < g.NV() && !hasCycle; v++) {
            if(status[v] == 0) dfs(v);
        }
    }
    vector<int> getOrder() {
        vector<int> result;
        if(hasCycle) return result;
        result = order;
        reverse(result.begin(), result.end());
        return result;
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
        order.push_back(v); //push after finished
    }
    const Graph& g;
    bool hasCycle; //has cycle
    vector<int> status; //vertex status during dfs (0: unvisited, 1: onstack, 2: finished)
    vector<int> order; //topological order
};

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        //construct directed graph
        Graph g(numCourses);
        for(auto c : prerequisites) 
            g.addEdge(c.second, c.first);
        //detect cycle using dfs
        TopoSort ts(g);
        ts.sort();
        return ts.getOrder();
    }
};

