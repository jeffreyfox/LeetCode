/*
There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.

A province is a group of directly or indirectly connected cities and no other cities outside of the group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.

 

Example 1:


Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2
Example 2:


Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
 

Constraints:

1 <= n <= 200
n == isConnected.length
n == isConnected[i].length
isConnected[i][j] is 1 or 0.
isConnected[i][i] == 1
isConnected[i][j] == isConnected[j][i]
*/

// Solution using union find (weighted quick-union with path compression).
class UnionFind {
  public:
    UnionFind(int n) : count(n) {
        parent.resize(n);
        for (int k = 0; k < n; ++k) parent[k] = k;
        weight.resize(n, 1);
    }
    int Find(int k) {
        while (parent[k] != k) {
            parent[k] = parent[parent[k]];
            k = parent[k];
        }
        return k;
    }
    void Union(int i, int j) {
        int pi = Find(i), pj = Find(j);
        if (pi == pj) return;
        if (weight[pi] < weight[pj]) {
            // attach smaller tree to the larger one
            parent[pi] = pj;
            weight[pj] += weight[pi];
        } else {
            parent[pj] = pi;
            weight[pi] += weight[pj];
        }
        count--;
    }
    // Number of connected components
    int Count() {
        return count;
    }
  private:
    vector<int> parent;
    vector<int> weight;
    int count;
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        if (n == 0) return 0;
        UnionFind uf(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (isConnected[i][j] == 1) {
                    uf.Union(i, j);
                }
            }
        }
        return uf.Count();
    }
};
