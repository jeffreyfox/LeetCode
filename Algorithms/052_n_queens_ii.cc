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
		vector<int> col(n, 0); //column number for Queen at each row
		int count = 0; //counter
		int irow = 0; //number of current row of Queen to be placed
		while(1) { //break inside
			if(irow == n) { //already found solution for last row
				count++; //update counter
				irow--; //retrace back to last row (check next solution)
				col[irow] ++; //try next position of last row
			} else if(col[irow] == n) { //exhausted all possibilities
				col[irow] = 0; //reset value back to 0
				irow --; //retrace back one row
				if(irow < 0) break; //breaking condition
				col[irow] ++; //try next position of last row
			} else if (isAttack(col, irow, col[irow])) {
				col[irow] ++; //try next column
			} else { //not attacking, move to next row
				irow++;
			}
		}
		return count;
	}
	//check if current queeen at row irow, column jcol attacks with previously placed queens
	bool isAttack(const vector<int>& col, int irow, int jcol) {
		for(int i = 0; i < irow; ++i) {
			if(col[i] == jcol || fabs(col[i] - jcol) == irow - i) return true;
		}
		return false;
	}
};
