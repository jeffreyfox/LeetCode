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
