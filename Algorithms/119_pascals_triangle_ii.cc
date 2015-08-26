/*
Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space? 
*/

// DP solution using O(k) space

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> currRow(rowIndex+1, 1);
        vector<int> nextRow(rowIndex+1, 1);
        currRow[0] = 1;
        for(int ir = 1; ir <= rowIndex; ++ir) { //ir has ir+1 elments [0 .. ir]
            nextRow[0] = nextRow[ir] = 1;
            for (int j = 1; j < ir; ++j)
                nextRow[j] = currRow[j-1] + currRow[j];
            currRow.swap(nextRow);
        }
        return currRow;
    }
};
