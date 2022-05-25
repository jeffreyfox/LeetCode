/*
You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given an array relations where relations[i] = [prevCoursei, nextCoursei], representing a prerequisite relationship between course prevCoursei and course nextCoursei: course prevCoursei has to be taken before course nextCoursei.

In one semester, you can take any number of courses as long as you have taken all the prerequisites in the previous semester for the courses you are taking.

Return the minimum number of semesters needed to take all courses. If there is no way to take all the courses, return -1.

 

Example 1:


Input: n = 3, relations = [[1,3],[2,3]]
Output: 2
Explanation: The figure above represents the given graph.
In the first semester, you can take courses 1 and 2.
In the second semester, you can take course 3.
Example 2:


Input: n = 3, relations = [[1,2],[2,3],[3,1]]
Output: -1
Explanation: No course can be studied because they are prerequisites of each other.
 

Constraints:

1 <= n <= 5000
1 <= relations.length <= 5000
relations[i].length == 2
1 <= prevCoursei, nextCoursei <= n
prevCoursei != nextCoursei
All the pairs [prevCoursei, nextCoursei] are unique.
*/

// Solution 1. Use BFS to do topological sorting
// Track the in-degree of each node.
// Maintain two queues, current level and next level.
// Start with nodes with in-degree of 0. Add to the current queue. When iterating over the current queue, add the neighbors with 0 in-degree to the next queue.
// Keep processing until the queue is empty.
// Needs to check if number of visited nodes equals total number of nodes.

class Graph {
public:
    Graph(int _V): V(_V) {
        adj.resize(V);
        indegree.resize(V);        
    }
    void addEdge(int v, int w) {
        adj[v].push_back(w);
        indegree[w]++;
    }
    int minSteps() {
        vector<int> curr, next;
        for (int v = 0; v < V; ++v) {
            if (indegree[v] == 0) curr.push_back(v);
        }
        while (!curr.empty()) {
            ++min_steps;
            for (const auto v : curr) {
                ++num_visited;
                for (const auto w : adj[v]) {
                    if (--indegree[w] == 0) {
                        next.push_back(w);
                    }
                }
            }
            curr = next;
            next.clear();
        }
        return num_visited == V ? min_steps : -1;
    }
private:
    int V;
    int min_steps = 0;
    int num_visited = 0;
    vector<vector<int>> adj;
    vector<int> indegree;    
};

class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        Graph g(n);
        for (const auto &r : relations) {
            g.addEdge(r[0]-1, r[1]-1);
        }
        return g.minSteps();
    }
};

// Solution 2. Use DFS and keep track of cycles and the maximum path lengths for each vertex.
// Uses an auxiliary vector to store results for visited vertices to avoid recomputation (memoization).
class Graph {
public:
    Graph(int _V): V(_V) {
        adj.resize(V);       
        visited.resize(V);
        on_stack.resize(V);
        path_length.resize(V);
    }
    void addEdge(int v, int w) {
        adj[v].push_back(w);     
    }
        
    int maxPathLength() {
        for (int v = 0; v < V; ++v) {
            if (!visited[v]) dfs(v);            
        }
        return has_cycle ? -1 : max_path_length;
    }

    void dfs(int v) {
        if (has_cycle) return;
        if (visited[v]) return;
        visited[v] = true;
        on_stack[v] = true;
        // The longest path length of vertex v
        int pl = 0;
        for (const int w : adj[v]) {
            if (on_stack[w]) {
                has_cycle = true;
                return;
            }
            if (!visited[w]) {
                dfs(w);                
            }
            pl = max(pl, path_length[w]);
        }
        on_stack[v] = false;
        path_length[v] = pl + 1;
        max_path_length = max(max_path_length, path_length[v]);
    }

private:
    int V;
    bool has_cycle = false;
    // The longest path length from the vertex to any of its sinks
    vector<int> path_length;
    // The longest path length among all vertices
    int max_path_length = 0;
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<bool> on_stack;
};

class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        Graph g(n);
        for (const auto &r : relations) {
            g.addEdge(r[0]-1, r[1]-1);
        }
        return g.maxPathLength();
    }
};
