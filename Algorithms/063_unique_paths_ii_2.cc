/// Space optimized DP solution, O(n) space with only one 1D array
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        //table[j]: number of paths from board[0][0] to boad[i][j], i < m; j < n;
        vector<int> table(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(obstacleGrid[i][j] == 1) table[j] = 0; //has obstacle, 0 paths
                else if (i == 0 && j == 0) table[j] = 1; //top left corner
                else if (i == 0) table[j] = table[j-1]; // top side boundary
                else if (j == 0) ; //table[j] = table[j]; // left side boundary
                else table[j] += table[j-1]; //interior cells
            }
        }
        return table[n-1];
    }
};
