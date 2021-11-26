/*
Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.
*/

// Solution 1. Recursive solution.
class Solution {
public:
    int totalNQueens(int n) {
        int count = 0;
        // keeps track of the position of queens on each row
        vector<int> queens(n, -1);        
        search(n, 0, queens, count);
        return count;
    }

    // Can we place a new queen at [row, col] position?
    bool canPlace(const vector<int> &queens, int row, int col) {
        // Check previous rows
        for (int i = 0; i < row; ++i) {
            int j = queens[i];
            // same column
            if (j == col) return false;
            // diagonal
            if (j - col == i - row) return false;
            // anti-diagonal
            if (j - col == row - i) return false;            
        }
        return true;
    }
    
    // place queens from row i
    void search(int n, int i, vector<int>& queens, int& count) {
        if (i == n) {
            count++;
            return;
        }
        // try all positions on row i
        for (int j = 0; j < n; ++j) {
            if (canPlace(queens, i, j)) {
                queens[i] = j;
                search(n, i+1, queens, count); 
                // No need to set queens[i] back to -1 because in canPlace we only check rows before |row|.
            }
        }     
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
