/// Proceed in a circular fashion, and outer to inner.
/// Each element, perform a 4-rotation with 3 counterparts
/// make sure the bounds for i and j are correct
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if(n == 0) return;
        
        for(int i = 0; i < n/2; ++i) {
            for(int j = i; j < n-1-i; ++j) {
                //4-rotation
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[n-1-j][i];
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                matrix[j][n-1-i] = tmp;
            }
        }
    }
};
