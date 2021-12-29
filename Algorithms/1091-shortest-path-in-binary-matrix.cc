/*
Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.

A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

All the visited cells of the path are 0.
All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
The length of a clear path is the number of visited cells of this path.

 

Example 1:


Input: grid = [[0,1],[1,0]]
Output: 2
Example 2:


Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
Output: 4
Example 3:

Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
Output: -1
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 100
grid[i][j] is 0 or 1
*/

class Solution {
public:
    struct Record {
        int i;
        int j;
        int d;
        Record() : i(-1), j(-1), d(0) {}
        Record(int _i, int _j, int _d) : i(_i), j(_j), d(_d) {}
    };

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if (grid[0][0] == 1 || grid[m-1][n-1] == 1) return -1;
        deque<Record> q;
        q.push_back(Record(0, 0, 1));
        set<pair<int, int>> visited;
        while (!q.empty()) {
            auto record = q.front(); q.pop_front();
            int i = record.i, j = record.j, d = record.d;
            if (i == m-1 && j == n-1) return d;
            visited.insert(make_pair(i, j));
            // check 8 directions:
            checkCell(i-1, j-1, d+1, grid, q, visited);
            checkCell(i-1, j, d+1, grid, q, visited);
            checkCell(i-1, j+1, d+1, grid, q, visited);
            checkCell(i, j-1, d+1, grid, q, visited);
            checkCell(i, j+1, d+1, grid, q, visited);
            checkCell(i+1, j-1, d+1, grid, q, visited);
            checkCell(i+1, j, d+1, grid, q, visited);
            checkCell(i+1, j+1, d+1, grid, q, visited);
        }
        return -1;
    }
    
    void checkCell(int i, int j, int d, const vector<vector<int>>& grid,
                   deque<Record> &q,
                  set<pair<int, int>> &visited) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n) return;
        if (grid[i][j] == 1) return;
        if (visited.count(make_pair(i, j))) return;
        visited.insert(make_pair(i, j));
        q.push_back(Record(i, j, d));
    }
};
