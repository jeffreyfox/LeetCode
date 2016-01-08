/*
Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/

// Straightforward solution. Commented unecessary checks for better efficiency. 0ms.

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int> > result;
        result.resize(numRows);
        for(int r = 0; r < numRows; ++r) {
            int n = r+1; //number of elements in this row
            result[r].resize(n, 1); //initialize as 1
            for(int i = 1; i < n-1; ++i)  result[r][i] = result[r-1][i-1] + result[r-1][i];
        }
        return result;
    }
};

// Solution 2, with unecessary checks. 4ms.
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int> > result;
        if(numRows == 0) return result;
        result.resize(numRows);
        result[0] = vector<int>(1, 1);
        for(int r = 1; r < numRows; ++r) {
            int n = r+1; //number of elements in this row
            result[r].resize(n, 1); //initialize as 1
            for(int i = 1; i < n-1; ++i)  result[r][i] = result[r-1][i-1] + result[r-1][i];
        }
        return result;
    }
};

