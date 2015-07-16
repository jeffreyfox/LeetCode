/// O(MN) time, O(1) space Algorithm
/// scan from top to bottom, and each row from right to left
/// use a boolean to track if current row contains any zeroes, and another to track if previous row contails any zeroes. Why
/// we need previous role will be explained later.
/// (a) If see an zero at (i, j), then set all elements above it to zero (only if the element directly above it is not zero), 
/// also label current row's boolean as true(contains one zero). 
/// (b) If see an element that is non-zero, check if the element above it is zero, if yes, then set this element as zero as well
/// The tricky part is we need to set any rows containing an zero all to zero. If we do this after finishing scanning a row,
/// then when we move to next line, the newly added zeroes will disrupt step (b). To avoid this, we only set entire row after
/// we finish step (b) for the next row. In other words, after we finish scanning row i, we set entire row i-1 to zero if needed
/// thus we need two variables to track the status of current and previous rows.

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if(m == 0) return;
        int n = matrix[0].size();
        if(n == 0) return;
       
        //whether last row, and current row has zero?
        bool last = false, curr = false;
        
        for(int i = 0; i < m; ++i) { //row
            
            for(int j = 0; j < n; ++j) { //column
                if(matrix[i][j] == 0) {
                    curr = true;
                    if(i > 0 && matrix[i-1][j] != 0) setColAbove(matrix, i, j);
                } else if(i > 0 && matrix[i-1][j] == 0) {
                    matrix[i][j] = 0; //set to zero
                }
            }
            
            //there is zero in the last line, set that row to zero
            if(last) setRow(matrix, i-1);
            
            last = curr;
            curr = false;
        }
        //don't forget the last row!
        if(last) setRow(matrix, m-1);
    }
    //set row i all to zero
    void setRow(vector<vector<int>>& matrix, int i) {
        for(int k = 0; k < matrix[i].size(); ++k) 
            matrix[i][k] = 0;
    }
    //set elements above row i, and at col j to zero
    void setColAbove(vector<vector<int>>& matrix, int i, int j) {
        for(int k = 0; k < i; ++k) 
            matrix[k][j] = 0;
    }
};
