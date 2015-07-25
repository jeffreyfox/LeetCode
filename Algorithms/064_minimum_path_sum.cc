// Dynamic programming, space-optimized version.
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
