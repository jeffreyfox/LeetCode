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

// BFS using a queue
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
