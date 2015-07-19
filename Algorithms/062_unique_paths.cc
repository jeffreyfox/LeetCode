/// Dynamic programming, space O(m*n). Can further optimize space usage to O(n).
/// First initialize all entries to 1 (cells at top, left sides have only 1 path). then start from 1 to end for DP construction.
class Solution {
public:
    int uniquePaths(int m, int n) {
        //table[i][j]: number of paths from board[0][0] to boad[i][j], i < m; j < n;
        vector<vector<int> > table(m, vector<int>(n, 1));
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                table[i][j] = table[i-1][j] + table[i][j-1];

        return table[m-1][n-1];
    }
};
