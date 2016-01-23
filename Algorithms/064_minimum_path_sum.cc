/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
*/

// Solution 1. Dynamic programming.

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int> > dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];
        for(int i = 1; i < m; ++i) dp[i][0] = dp[i-1][0] + grid[i][0];
        for(int j = 1; j < n; ++j) dp[0][j] = dp[0][j-1] + grid[0][j];
        for(int i = 1; i < m; ++i) {
            for(int j = 1; j < n; ++j) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[m-1][n-1];
    }
};

// Solution 2. Dynamic programming, space-optimized version.
// Be aware of initial values of the 1D array!

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> sum(n, INT_MAX);
        sum[0] = 0;
        for (int i = 0; i < m; ++i) {
            sum[0] += grid[i][0];
            for (int j = 1; j < n; ++j)
                sum[j] = min(sum[j-1], sum[j]) + grid[i][j];
        }
        return sum[n-1];
    }
};
