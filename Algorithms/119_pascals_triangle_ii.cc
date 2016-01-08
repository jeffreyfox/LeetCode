/*
Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space? 
*/

// DP solution using only one vector. And avoided uncessary checks. Use an "old" variable to store the old value of current index, to be used for getting sum for the next element.

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> result(rowIndex+1, 1); //initialize as 1        
        for(int r = 2; r <= rowIndex; ++r) {
            int tmp = 0, old = 1;
            for(int i = 1; i < r; ++i) {
                tmp = result[i]; //store old value in temporary
                result[i] += old;
                old = tmp; //update old value
            }
        }
        return result;
    }
};

// Same as above. With additional unecessary checks.
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if(rowIndex == 0) return vector<int>(1, 1);
        if(rowIndex == 1) return vector<int>(2, 1);
        vector<int> result(rowIndex+1, 0); //initialize as 0
        result[0] = result[1] = 1; 

        for(int r = 2; r <= rowIndex; ++r) {
            int n = r + 1;
            int tmp = 0, old = 1;
            for(int i = 1; i < n-1; ++i) {
                tmp = result[i]; //store old value in temporary
                result[i] += old;
                old = tmp; //update old value
            }
            result[n-1] = 1;
        }
        return result;
    }
};

// DP solution using two vectors. swapping.

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
