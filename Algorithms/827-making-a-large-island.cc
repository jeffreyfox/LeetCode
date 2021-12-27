/*
You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.

Return the size of the largest island in grid after applying this operation.

An island is a 4-directionally connected group of 1s.

 

Example 1:

Input: grid = [[1,0],[0,1]]
Output: 3
Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
Example 2:

Input: grid = [[1,1],[1,0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
Example 3:

Input: grid = [[1,1],[1,1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 4.
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 500
grid[i][j] is either 0 or 1.
*/

// Use union find to find connected groups.
// Then check every 0 in the board. Use a map to track connected components near the candidate position.
// Also use a boolean to handle the corner case of a full board (all 1's).
class UnionFind {
public:
    UnionFind(int m) {
        parent.resize(m, 0);
        for (int i = 0; i < m; ++i) {
            parent[i] = i;
        }
        sz.resize(m, 1);
    }
    
    int size(int i) {  return sz[Find(i)]; }
   
    int Find(int i) {
        while (parent[i] != i) {
            parent[i] = parent[parent[i]];
            i = parent[i];
        }
        return i;
    }
    
    void Union(int i, int j) {
        int pi = Find(i);
        int pj = Find(j);
        if (pi == pj) return;
        if (sz[pi] < sz[pj]) {
            parent[pi] = pj;
            sz[pj] += sz[pi];
        } else {
            parent[pj] = pi;
            sz[pi] += sz[pj];
        }
    }
private:
    vector<int> parent;
    vector<int> sz;
};

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        UnionFind uf(n*n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 1) continue;
                if (i < n-1 && grid[i+1][j] == 1) uf.Union(i*n+j, (i+1)*n+j);
                if (j < n-1 && grid[i][j+1] == 1) uf.Union(i*n+j, i*n+j+1);
            }
        }
        
        int result = 0;
        bool found_zero = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) continue;
                found_zero = true;
                
                unordered_map<int, int> dict;                
                if (i > 0 && grid[i-1][j] == 1) {
                    int idx = (i-1)*n+j;
                    dict[uf.Find(idx)] = uf.size(idx);
                }
                if (i < n-1 && grid[i+1][j] == 1) {
                    int idx = (i+1)*n+j;
                    dict[uf.Find(idx)] = uf.size(idx);
                }
                if (j > 0 && grid[i][j-1] == 1) {
                    int idx = i*n+j-1;
                    dict[uf.Find(idx)] = uf.size(idx);
                }
                if (j < n-1 && grid[i][j+1] == 1) {
                    int idx = i*n+j+1;
                    dict[uf.Find(idx)] = uf.size(idx);
                }
                int res = 1;
                for (auto [_, count] : dict) {
                    res += count;
                }
                result = max(result, res);
            }
        }
        return found_zero ? result : n*n;
    }

    int getIndex(int i, int j, int n) { return i*n + j; }
};
