/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

Above is a 3 x 7 grid. How many possible unique paths are there? 

Note: m and n will be at most 100.
*/

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

/// Space optimized solution, O(n) space using only one array
class Solution {
public:
    int uniquePaths(int m, int n) {
        //table[j]: number of paths from board[0][0] to boad[i][j], i < m; j < n;
        vector<int> table(n, 1);
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                table[j] += table[j-1];

        return table[n-1];
    }
};

