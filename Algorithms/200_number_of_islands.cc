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

//Standard DFS
// Note that we have to check 4 neighbors! Only checking right and bottom is not enough! See the case below:

// 1 1 1
// 0 1 0
// 1 1 1
// Starting from left top corner, if only checking 2 neighbors, we missed the bottom left one, and we end up count = 2.

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        for(int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(grid[i][j] == '1') {
                    dfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
    void dfs(vector<vector<char> >& grid, int i, int j) {
        grid[i][j] = '0';
        //check 4 neighbors
        if(i > 0 && grid[i-1][j] == '1') dfs(grid, i-1, j); //top
        if(j > 0 && grid[i][j-1] == '1') dfs(grid, i, j-1); //left
        if(i < grid.size()-1    && grid[i+1][j] == '1') dfs(grid, i+1, j); //bottom
        if(j < grid[i].size()-1 && grid[i][j+1] == '1') dfs(grid, i, j+1); //right
    }
};
