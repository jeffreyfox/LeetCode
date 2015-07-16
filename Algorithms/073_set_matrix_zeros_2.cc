/// Two pass O(MN) time, O(m+n) space algorithm
/// Use two arrays to track if a given row/column has zero

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(); 
        if(m == 0) return; 
        int n = matrix[0].size(); 
        if(n == 0) return; 
        
        vector<bool> rows(m, false);
        vector<bool> cols(n, false);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(matrix[i][j] == 0) rows[i] = cols[j] = true;
            }
        }
        
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(rows[i] || cols[j]) matrix[i][j] = 0;
            }
        }
    }
};
