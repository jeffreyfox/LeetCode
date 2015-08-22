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

// Straightforward solution. Commented unecessary checks for better efficiency

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int> > ret;
        //if(numRows == 0) return ret;
        for(int ir = 1; ir <= numRows; ++ir) {
            ret.push_back(vector<int>(ir, 1));
           // if(ir <= 2) continue;
            for(int j = 1; j < ir-1; ++j) { //elements [1 .. ir-2], a total of ir-2
                ret[ir-1][j] = ret[ir-2][j] + ret[ir-2][j-1];
            }
        }
        return ret;
    }
};
