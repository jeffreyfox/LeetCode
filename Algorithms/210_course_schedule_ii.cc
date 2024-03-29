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
    Graph(int _V) : V(_V), has_cycle(false) {
        adj.resize(V);
        visited.resize(V, false);
        on_stack.resize(V, false);
    }
    void addEdge(int v, int w) { adj[v].push_back(w); }
    vector<int> topoSort() {
        for (int v = 0; v < V; ++v) {
            if (!visited[v]) dfs(v);
        }
        if (has_cycle) return {};
        std::reverse(topo_sorted.begin(), topo_sorted.end());
        return topo_sorted;
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
        topo_sorted.push_back(v);
    }
    bool hasCycle() { return has_cycle; }
    
private:
    int V;
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<bool> on_stack;
    vector<int> topo_sorted;
    bool has_cycle;
};

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        Graph g(numCourses);
        for (const auto &pre : prerequisites) {
            g.addEdge(pre[1], pre[0]);
        }
        return g.topoSort();          
    }
};
