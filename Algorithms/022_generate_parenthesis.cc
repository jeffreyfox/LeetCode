/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()" 
*/

// Recursive solution. backtracking, DFS
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string tmp;
        search(n, n, tmp, result);   
        return result;
    }
    // choose the next chars from num_left '(' and num_right ')'
    void search(int num_left, int num_right, string &tmp, vector<string> &result) {
        if (num_left == 0 && num_right == 0) {
            result.push_back(tmp);
            return;
        }
        tmp.push_back(' ');
        if (num_left > 0) {
            tmp.back() = '(';  // put '('
            search(num_left - 1, num_right, tmp, result);
        }
        if (num_right > 0 && num_left < num_right) {
            tmp.back() = ')';  // put ')'
            search(num_left, num_right - 1, tmp, result);
        }
        tmp.pop_back();
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
