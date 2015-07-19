/// Dynamic programming O(m*n) space solution.
/// Only one nested loop

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        //table[i][j]: number of paths from board[0][0] to boad[i][j], i < m; j < n;
        vector<vector<int> > table(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(obstacleGrid[i][j] == 1) table[i][j] = 0; //has obstacle, 0 paths
                else if (i == 0 && j == 0) table[i][j] = 1; //top left corner
                else if (i == 0) table[i][j] = table[i][j-1]; // top side boundary
                else if (j == 0) table[i][j] = table[i-1][j]; // left side boundary
                else table[i][j] = table[i-1][j] + table[i][j-1]; //interior cells
            }
        }
        return table[m-1][n-1];
    }
};
