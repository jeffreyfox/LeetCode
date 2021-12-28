/*
Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.

 

Example 1:


Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,4,7,5,3,6,8,9]
Example 2:

Input: mat = [[1,2],[3,4]]
Output: [1,2,3,4]
 

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
-105 <= mat[i][j] <= 105
*/

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        vector<int> result;
        int m = mat.size(), n = mat[0].size();
        int level = 0;
        bool reverse = false;
        for (int level = 0; level < m+n-1; ++level) {
            if (reverse) {
                for (int col = min(n-1, level), row = level - col; col >= 0 && row < m; col--, row++) {
                    result.push_back(mat[row][col]);
                }
            } else {
                for (int row = min(m-1, level), col = level - row; row >= 0 && col < n; row--, col++) {
                    result.push_back(mat[row][col]);
                }
            }
            reverse = !reverse;
        }
        return result;
    }
};
