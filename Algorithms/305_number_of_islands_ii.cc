/*
A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example:

Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0

Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0

Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0

Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0

Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

1 1 0
0 0 1   Number of islands = 3
0 1 0

We return the result as an array: [1, 1, 2, 3]

Challenge:

Can you do it in time complexity O(k log mn), where k is the length of the positions?
*/

// Weighted union find with path compression by halving.
// See Solution to Problem 200 for details.

class UnionFind {
public:
    UnionFind(int N) : n(0) {
        id.resize(N, -1);
        size.resize(N, 0);
    }
    void add(int i) {
        id[i] = i; size[i] = 1;
        n++;
    }
    void uni(int i, int j) {
        if(id[j] == -1) return; //only add valid ones
        while(id[i] != i) { id[i] = id[id[i]]; i = id[i]; }
        while(id[j] != j) { id[j] = id[id[j]]; j = id[j]; }
        if(i != j) {
            if(size[i] < size[j]) { id[i] = j; size[j] += size[i]; }
            else { id[j] = i; size[i] += size[j]; }
            n--;
        }
    }

    int count() const { return n; }

private:
    vector<int> id;
    vector<int> size;
    int n;
};

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        int size = positions.size();
        vector<int> result(size, 0);
        UnionFind uf(m*n);
        for(int i = 0; i < size; ++i) {
            const int &x = positions[i].first, &y = positions[i].second;
            int idx = x*n+y;
            uf.add(idx);
            //check four neighbors
            if(x > 0) uf.uni(idx, idx-n);
            if(x < m-1) uf.uni(idx, idx+n);
            if(y > 0) uf.uni(idx, idx-1);
            if(y < n-1) uf.uni(idx, idx+1);
            result[i] = uf.count();
        }
        return result;
    }
};

