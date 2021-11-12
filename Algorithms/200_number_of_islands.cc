/*
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000

Answer: 1

Example 2:

11000
11000
00100
00011

Answer: 3
*/

//Solution 1: Standard DFS
// Note that we have to check 4 neighbors! Only checking right and bottom is not enough! See the case below:

// 1 1 1
// 0 1 0
// 1 1 1
// Starting from left top corner, if only checking 2 neighbors, we missed the bottom left one, and we end up count = 2.

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    count++;
                    dfs(grid, m, n, i, j);
                }
            }
        }
        return count;
    }
    
    void dfs(vector<vector<char>>&grid, int m, int n, int i, int j) {
        if (i < 0 || i >= m || j < 0 || j >= n) return;
        if (grid[i][j] != '1') return;
        // mark as visited
        grid[i][j] = 'x';
        dfs(grid, m, n, i+1, j);
        dfs(grid, m, n, i-1, j);
        dfs(grid, m, n, i, j+1);
        dfs(grid, m, n, i, j-1);        
    }
};

// Solution 2: BFS using a queue
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        for(int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(grid[i][j] == '1') {
                    bfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
    void bfs(vector<vector<char> >& grid, int i, int j) {
        deque<pair<int, int> > q;
        q.push_back(make_pair(i, j)); 
        grid[i][j] = '0';
        while (!q.empty()) {
            int ni = q.front().first;
            int nj = q.front().second;
            q.pop_front();
            //check 4 neighbors
            if(ni > 0 && grid[ni-1][nj] == '1') { grid[ni-1][nj] = '0'; q.push_back(make_pair(ni-1, nj)); } //top
            if(nj > 0 && grid[ni][nj-1] == '1') { grid[ni][nj-1] = '0'; q.push_back(make_pair(ni, nj-1)); } //left
            if(ni < grid.size()-1    && grid[ni+1][nj] == '1') { grid[ni+1][nj] = '0'; q.push_back(make_pair(ni+1, nj)); } //bottom
            if(nj < grid[ni].size()-1 && grid[ni][nj+1] == '1') { grid[ni][nj+1] = '0'; q.push_back(make_pair(ni, nj+1)); } //right
        }
    }
};

// Solution 3: Union find.
// Record the total number of disjoint sets. m*n elements, initially all inactive. Scan the grid, when finding a '1', mark the element as active, and set its id and size attributes in UnionFind class. Maintain a conversion formula from 2D positions to 1D index (i*n+j).
// Use weighted union find with path compression, close to O(n) time complexity.
// Caveats:
// 1. 1D index is i*n+j, not i*m+j!
// 2. we need to check left and top neighbors, can skip bottom and right neighbors. Since we are scanning strictly top-down, left-right. 

class UnionFind {
public:
    UnionFind(int N) : n(0) {
        id.resize(N, -1);
        size.resize(N, 0);
    }
    //add element i as a new set
    void add(int i) {
        id[i] = i;
        size[i] = 1;
        n++;
    }
    //unite two elements
    void unite(int i, int j) {
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
    vector<int> id; //set id
    vector<int> size; //size of each set
    int n; //total number of sets
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        UnionFind uf(m*n);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == '0') continue;
                int idx = i*n+j;
                uf.add(idx); //add to sets
                if(i > 0 && grid[i-1][j] == '1')  //top neighbor
                    uf.unite(idx, idx-n);
                if(j > 0 && grid[i][j-1] == '1') //left neighbor
                    uf.unite(idx, idx-1);
            }
        }
        return uf.count();        
    }
};

