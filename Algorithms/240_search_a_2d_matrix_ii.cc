/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

    Integers in each row are sorted in ascending from left to right.
    Integers in each column are sorted in ascending from top to bottom.

For example,

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]

Given target = 5, return true.

Given target = 20, return false.
*/

//O(m+n) solution. Two pointers, one at left top corner, other at bottom right corner. Compare value at top right corner with target.
// If smaller than target, then the top row can be excluded (left top corner can be moved down by one step).
// If larger than target, then the rightmost row can be excluded (right bottom corner can be moved left by one step).

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;
        int m = matrix.size(), n = matrix[0].size();
        int xlo = 0, ylo = 0, xhi = m-1, yhi = n-1;
        while(xlo <= xhi && ylo <= yhi) {
            int val = matrix[xlo][yhi];
            if(target == val) return true;
            else if(target > val) xlo++; 
            else yhi--;
        }
        return false;
    }
};

// Solution 2. Divide and conquer. Longer than Solution 1.

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        int m = matrix.size(), n = matrix[0].size();
        return search(matrix, 0, 0, m-1, n-1, target);
    }
    bool search(vector<vector<int> >& matrix, int xl, int yl, int xh, int yh, int target) {
        if (xl > xh || yl > yh) return false;
        int xm = xl + (xh - xl) / 2;
        int ym = yl + (yh - yl) / 2;
        int v = matrix[xm][ym];
        if (target < v) return search(matrix, xl, yl, xh, ym-1, target) || search(matrix, xl, ym, xm-1, yh, target);
        else if (target > v) return search(matrix, xl, ym+1, xh, yh, target) || search(matrix, xm+1, yl, xh, ym, target);
        else return true;
    }
};

