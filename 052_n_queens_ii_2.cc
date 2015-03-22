//recursive solution
class Solution {
public:
    int totalNQueens(int n) {
        vector<int> col(n, -1);
        int count = 0;
        solveUtil(n, 0, col, count);
        return count;
    }
    
	//check row i
	void solveUtil(int n, int i, vector<int> &col, int &count) {
	    if(i == n) { 
	        count ++;
	        return;
	    }
		for(int j = 0; j < n; ++j) { //try the j-th column
			if(canPlace(col, i, j)) {
				col[i] = j;
				solveUtil(n, i+1, col, count); //next row
			}
		}
		col[i] = -1; //not found a solution, backtrace
	}
	
	//check attacking positions of already placed ones
	bool canPlace(vector<int> &col, int i, int j) {
		for(int k = 0; k < i; ++k) {
			if(j == col[k] || std::abs(col[k] - j) == i - k) return false;
		}
		return true;
	}
};
