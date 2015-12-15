/*
Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:

Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10

Note:

    The matrix is only modifiable by the update function.
    You may assume the number of calls to update and sumRegion function is distributed evenly.
    You may assume that row1 ≤ row2 and col1 ≤ col2.
*/

// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.update(1, 1, 10);
// numMatrix.sumRegion(1, 2, 3, 4);

// 2D binary indexed tree.

class NumMatrix {
public:
    NumMatrix(vector<vector<int>> &matrix) {
        if(matrix.empty() || matrix[0].empty()) {
            m = n = 0;
            return;
        }
        m = matrix.size(); n = matrix[0].size();
        bitsum.resize(m+1, vector<int>(n+1, 0));
        num.resize(m+1, vector<int>(n+1, 0));
        for(int i = 0; i < m; ++i) 
            for(int j = 0; j < n; ++j)
                update(i, j, matrix[i][j]);
    }

    void update(int row, int col, int val) {
        int delta = val - num[++row][++col];
        num[row][col] = val;
        int irow = row, jcol = col;
        while(irow <= m) {
           jcol = col;
           while(jcol <= n) {
               bitsum[irow][jcol] += delta;
               jcol += (jcol & (-jcol));
           }
           irow += (irow & (-irow));
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return getSum(row2, col2) - getSum(row1-1, col2) - getSum(row2, col1-1) + getSum(row1-1, col1-1);
    }

private:
    //get sum from [0, 0] to [row, col]
    int getSum(int row, int col) {
        if(row < 0 || row >= m || col < 0 || col >= n) return 0;
        row++; col++;
        int sum = 0;
        int irow = row, jcol = col;
        while(irow > 0) {
            jcol = col;
            while(jcol > 0) {
                sum += bitsum[irow][jcol];
                jcol -= (jcol & (-jcol));
            }
            irow -= (irow & (-irow));
        }
        return sum;
        
    }
    int m, n;
    vector<vector<int> > bitsum, num;
};

