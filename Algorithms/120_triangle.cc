/*
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]

The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle. 
*/

// Standard DP

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.empty()) return 0;
        int ret = INT_MAX;
        int nr = triangle.size();
        vector<int> currRow(nr, INT_MAX);
        vector<int> nextRow(nr, INT_MAX);
        //row 0:
        currRow[0] = triangle[0][0];
        for (int ir = 1; ir < nr; ++ir) { //ir has ir+1 elements in triangle (0 .. ir)
            nextRow[0] = currRow[0] + triangle[ir][0];
            for (int j = 1; j < ir; ++j)
                nextRow[j] = min(currRow[j-1], currRow[j]) + triangle[ir][j];
            nextRow[ir] = currRow[ir-1] + triangle[ir][ir];
            currRow.swap(nextRow);
        }
        for (size_t i = 0; i < currRow.size(); ++i) {
            ret = min(ret, currRow[i]);
        }
        return ret;
    }
};
