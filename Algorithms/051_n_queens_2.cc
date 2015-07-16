//recursive solution
class Solution {
public:
	vector<vector<string> > solveNQueens(int n) {
		vector<int> col(n, -1);
		vector<vector<string> > ret;
		solveUtil(n, 0, col, ret);
		return ret;
	}
    
	//check row i
	void solveUtil(int n, int i, vector<int> &col, vector<vector<string> > &ret) {
		if(i == n) { 
			saveSol(n, col, ret);
			return;
		}
		
		for(int j = 0; j < n; ++j) { //try the j-th column
			if(canPlace(col, i, j)) {
				col[i] = j;
				solveUtil(n, i+1, col, ret); //next row
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
	
	void saveSol(int n, vector<int> &col, vector<vector<string> > &ret) {
		vector<string> tmp;
		for(int i = 0; i < n; ++i) {
			string str(n, '.');
			str[col[i]] = 'Q';
			tmp.push_back(str);
		}
		ret.push_back(tmp);
	}
};
