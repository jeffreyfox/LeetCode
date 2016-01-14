/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

    Integers in each row are sorted from left to right.
    The first integer of each row is greater than the last integer of the previous row.

For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]

Given target = 3, return true.
*/

//binary search. Convert 1D index to 2D index

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0) return false;
        int n = matrix[0].size();
        if (n == 0) return false;
        int lo = 0, hi = m*n-1, mid = 0;
        // invariant:
        // [0 .. lo-1] < target
        // [lo .. hi] to be checked
        // [hi+1 .. m*n-1] > target
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            int v = matrix[mid/n][mid%n];
            if (v < target) lo = mid + 1;
            else if (v > target) hi = mid - 1;
            else return true;
        }
        return false;
    }
};
