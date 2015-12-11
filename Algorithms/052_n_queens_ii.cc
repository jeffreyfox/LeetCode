/*
Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.
*/

// Solution 1. Recursive solution.

class Solution {
public:
    int totalNQueens(int n) {
        if(n == 0) return 0;
        int count = 0;
        vector<int> pos(n, -1); //position of queen in row[i], can be between 0 and n-1
        return solveNQueensHelper(0, pos);
    }
    //checking row i
    int solveNQueensHelper(int i, vector<int>& pos) {
        int n = pos.size();
        if(i == n) return 1;
        int count = 0;
        //try position j on row i (no queens will be on the same row)
        for(int j = 0; j < n; ++j) {
           if(canPlace(i, j, pos)) {
              pos[i] = j;
              count += solveNQueensHelper(i+1, pos);
           }
        }
        pos[i] = -1; //reset value
        return count;
    }
    //can place, check if Queen at [i][j] conflicts with queens in previous rows
    bool canPlace(int i, int j, vector<int>& pos) {
        for(int row = 0; row < i; ++row) {
            int col = pos[row];
            if(col == j || fabs(j - col) == i - row) return false;   //same col or diagonal
        }
        return true;
    }
};


// Solution 2. Iterative solution.

class Solution {
public:
    int totalNQueens(int n) {
        if(n == 0) return 0;
        int count = 0;
        vector<int> pos(n, -1); //position of queen in row[i], can be between 0 and n-1
        int i = 0, j = 0;
        while(i >= 0) {
            if(i == n) {
                count++;
                i--; //retrace back
                continue;
            }
            j = pos[i]+1; //move one step to right and try new positions
            while(j < n && !canPlace(i, j, pos)) j++;
            if(j == n) { //tried all possibilities, retrace back
                pos[i] = -1; i--;
                continue;
            }
            //found a possible place, record and move to next row.
            pos[i] = j;  i++;
        }
        return count;
    }

    //can place, check if Queen at [i][j] conflicts with queens in previous rows
    bool canPlace(int i, int j, vector<int>& pos) {
        for(int row = 0; row < i; ++row) {
            int col = pos[row];
            if(col == j || fabs(j - col) == i - row) return false;   //same col or diagonal
        }
        return true;
    }
};
