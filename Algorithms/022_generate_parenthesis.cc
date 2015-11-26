/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()" 
*/

// Recursive solution. backtracking, DFS
// pre-allocate string, pass reference and string index to avoid string copying. Keep track of number of open and close brackets left.

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        if(n < 1) return result;
        string tmp(2*n, '0');
        dfs(n, n, 0, tmp, result);
        return result;
    }
    void dfs(int nOpen, int nClose, int i, string& tmp, vector<string>& result) {
        if(nOpen < 0 || nClose < 0 || nOpen > nClose) return;
        
        if(i == tmp.size()) {
            result.push_back(tmp);
            return;
        }
        
        tmp[i] = '(';
        dfs(nOpen-1, nClose, i+1, tmp, result);
        
        tmp[i] = ')';
        dfs(nOpen, nClose-1, i+1, tmp, result);
    }
};

// Another iterative solution
class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> ret;
		int k(0); //k is the index of current parenthesis
		int nr(0); //number of left and right parenthesis
		string str(2*n, '('); //initially '('
		while(1) {
			int nl = k+1-nr;
			if(k == 2*n) { //reached end of string, add to solution
				ret.push_back(str);
				k--;
				update(str[k], nr);
			} else if (str[k] == 'X') { //exhaust all trials, abandon and retrace
				update(str[k], nr); //reset to '.'
				k--;
				if(k < 0) break; //breaking condition
				update(str[k], nr); //increment last element
			} else if(nr > n || nl > n || nl < nr){ //unbalanced
				update(str[k], nr);
			} else { //normal
				k++;
			}
		}
		return ret;
	}
	void update(char& c, int& nr) {
		if(c == '(') {
			c = ')';
			nr ++;
		} else if(c == ')') {
			c = 'X';
			nr --;
		}	else if(c == 'X') c = '(';
	}
};
