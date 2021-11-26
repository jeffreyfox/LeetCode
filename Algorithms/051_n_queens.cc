/*
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]

*/

/*
Solution 1. Recursive DFS.
use a vector to keep track of the column position of queens in each row.
This way it is guaranteed that no queen are on the same row.
We only need to check if the current queen is on the same column or same diagonal with any previously placed queens.

Use a matrix for string to prestore the solutions, when found solution, update string matrix, push to solution, and reset string matrix back.
*/

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        // keeps track of the position of queens on each row
        vector<int> queens(n, -1);
        search(n, 0, queens, result);
        return result;
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
    // Generates the solution string from the queen positions
    vector<string> GenerateSolution(const vector<int> &queens) {
        int n = queens.size();
        vector<string> result;
        result.reserve(n);        
        for (int i = 0; i < n; ++i) {
            string s(n, '.');
            s[queens[i]] = 'Q';
            result.push_back(s);
        }
        return result;
    }
    // place queens from row i
    void search(int n, int i, vector<int>& queens, vector<vector<string>>& result) {
        if (i == n) {
            result.push_back(GenerateSolution(queens));
            return;
        }
        // try all positions on row i
        for (int j = 0; j < n; ++j) {
            if (canPlace(queens, i, j)) {
                queens[i] = j;
                search(n, i+1, queens, result); 
                // No need to set queens[i] back to -1 because in canPlace we only check rows before |row|.
            }
        }
    }
};

// Solution 2. Iterative solution.

class Solution {
public:
	vector<vector<string> > solveNQueens(int n) {
		vector<vector<string> > ret;
		int irow = 0;
		vector<int> col(n,-1);
		while(irow >= 0) { 
		    if(irow == n) { //found a solution
		        ret.push_back(config2str(col));
		        irow--; //retrace
		    } else {
			    //find next valid column position
			    col[irow] ++;
			    while(col[irow] < n && !isValid(col, irow)) col[irow]++;
			
			    if(col[irow] == n) {  // tried all combinations, retrace
			        col[irow] = -1;
			        irow--; 
    			} else {  //suceeded at k-th step, move to next
    			    irow++;
				}
			}
		}
		return ret;
	}
	
	bool isValid(const vector<int>& col, int irow) { 
		for(int j = 0; j < irow; ++j) {
			if(col[j] == col[irow] || irow - j == std::fabs(col[irow] - col[j])) return false;
		}
		return true; 
	}
	
	vector<string> config2str(const vector<int>& conf) {
		vector<string> ret;
		string str;
		for(int k = 0; k < conf.size(); ++k) { //k-th string
			str.clear();
			for(int j = 0; j < conf.size(); ++j) {
				if(conf[k] == j) str += 'Q';
				else str += '.';
			}
			ret.push_back(str);
		}
		return ret;
	}
};
