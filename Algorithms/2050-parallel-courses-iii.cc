/*
You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given a 2D integer array relations where relations[j] = [prevCoursej, nextCoursej] denotes that course prevCoursej has to be completed before course nextCoursej (prerequisite relationship). Furthermore, you are given a 0-indexed integer array time where time[i] denotes how many months it takes to complete the (i+1)th course.

You must find the minimum number of months needed to complete all the courses following these rules:

You may start taking a course at any time if the prerequisites are met.
Any number of courses can be taken at the same time.
Return the minimum number of months needed to complete all the courses.

Note: The test cases are generated such that it is possible to complete every course (i.e., the graph is a directed acyclic graph).

 

Example 1:


Input: n = 3, relations = [[1,3],[2,3]], time = [3,2,5]
Output: 8
Explanation: The figure above represents the given graph and the time required to complete each course. 
We start course 1 and course 2 simultaneously at month 0.
Course 1 takes 3 months and course 2 takes 2 months to complete respectively.
Thus, the earliest time we can start course 3 is at month 3, and the total time required is 3 + 5 = 8 months.
Example 2:


Input: n = 5, relations = [[1,5],[2,5],[3,5],[3,4],[4,5]], time = [1,2,3,4,5]
Output: 12
Explanation: The figure above represents the given graph and the time required to complete each course.
You can start courses 1, 2, and 3 at month 0.
You can complete them after 1, 2, and 3 months respectively.
Course 4 can be taken only after course 3 is completed, i.e., after 3 months. It is completed after 3 + 4 = 7 months.
Course 5 can be taken only after courses 1, 2, 3, and 4 have been completed, i.e., after max(1,2,3,7) = 7 months.
Thus, the minimum time needed to complete all the courses is 7 + 5 = 12 months.
 

Constraints:

1 <= n <= 5 * 104
0 <= relations.length <= min(n * (n - 1) / 2, 5 * 104)
relations[j].length == 2
1 <= prevCoursej, nextCoursej <= n
prevCoursej != nextCoursej
All the pairs [prevCoursej, nextCoursej] are unique.
time.length == n
1 <= time[i] <= 104
The given graph is a directed acyclic graph.
*/

// Solution using DFS. Compute the maximum path sum (weighted) for each vertex to any of its sinks
class Graph {
public:
    Graph(int _V, const vector<int> &_weight): V(_V), weight(_weight) {
        adj.resize(V);       
        visited.resize(V);
        on_stack.resize(V);
        path_sum.resize(V);
    }
    void addEdge(int v, int w) {
        adj[v].push_back(w);     
    }
        
    int maxPathSum() {
        for (int v = 0; v < V; ++v) {
            if (!visited[v]) dfs(v);            
        }
        return has_cycle ? -1 : max_path_sum;
    }

    void dfs(int v) {
        if (has_cycle) return;
        if (visited[v]) return;
        visited[v] = true;
        on_stack[v] = true;
        // The path sum of vertex v
        int ps = 0;
        for (const int w : adj[v]) {
            if (on_stack[w]) {
                has_cycle = true;
                return;
            }
            if (!visited[w]) {
                dfs(w);                
            }
            ps = max(ps, path_sum[w]);
        }
        on_stack[v] = false;
        path_sum[v] = weight[v] + ps;
        max_path_sum = max(max_path_sum, path_sum[v]);
    }

private:
    int V;
    bool has_cycle = false;    
    // The weight of each vertex (time it takes to complete the course)
    vector<int> weight;
    // The path sum of each vertex (the maximum accumulated weights from the vertex to any of its sinks)
    vector<int> path_sum;
    // The maximum weighted path sum among all vertices
    int max_path_sum = 0;
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<bool> on_stack;
};

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        Graph g(n, time);
        for (const auto &r : relations) {
            g.addEdge(r[0]-1, r[1]-1);
        }
        return g.maxPathSum();
    }
};
