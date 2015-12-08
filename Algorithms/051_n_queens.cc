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
        vector<vector<string> > result;
        if(n == 0) return result;
        vector<int> pos(n, -1); //position of queen in row[i], can be between 0 and n-1
        vector<string> solstr(n, string(n, '.'));
        solveNQueensHelper(0, pos, solstr, result);
        return result;
    }
    //checking row i
    void solveNQueensHelper(int i, vector<int>& pos, vector<string>& solstr, vector<vector<string> >& result) {
        int n = pos.size();
        if(i == n) {
            //construct solution
            for(size_t i = 0; i < pos.size(); ++i) {
                solstr[i][pos[i]] = 'Q';
            }
            result.push_back(solstr);
            //reset solstr
            for(size_t i = 0; i < pos.size(); ++i) {
                solstr[i][pos[i]] = '.';
            }
            return;
        }
        //try position j on row i (no queens will be on the same row)
        for(int j = 0; j < n; ++j) {
           if(canPlace(i, j, pos)) {
              pos[i] = j;
              solveNQueensHelper(i+1, pos, solstr, result);
           }
        }
        pos[i] = -1; //reset value
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
