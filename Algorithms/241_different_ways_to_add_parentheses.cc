/*
Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.

Example 1

Input: "2-1-1".

((2-1)-1) = 0
(2-(1-1)) = 2

Output: [0, 2]

Example 2

Input: "2*3-4*5"

(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10

Output: [-34, -14, -10, -10, 10]
*/

// Dynamic programming solution.
// First parse string and save numbers and operators separately.
// Then start from bottom up, for large string break into small pieces and check all options.

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        if(input.empty()) return vector<int>();
        vector<int> nums; 
        vector<char> ops;
        parse(input, nums, ops);
        int n = nums.size(); //number of numbers
        //mp[i][j]: outcomes from i (i = [0..n]) numbers starting at j (j = [0 .. n-1]). 
        vector<vector<vector<int> > > mp(n+1, vector<vector<int> >(n, vector<int>()));
        //len = 1 case
        for(int i = 0; i < n; ++i) {
           mp[1][i].push_back(nums[i]);
        }
        for(int len = 2; len <= n; ++len) {
            for (int i = 0; i + len <= n; ++i) {
                int j = i + len - 1; //i start, j end, inclusive
                //try to break it from i+1 .. to j-1
                for(int k = i; k < j; ++k) { // break like this: num[k] | op[k] | num[k+1]
                    for(auto it1 : mp[k-i+1][i]) {
                        for(auto it2 : mp[j-k][k+1]) {
                            mp[len][i].push_back(eval(it1, it2, ops[k]));
                        }
                    }
                }
            }
        }
        return mp[n][0];
    }
    
    int eval(int v1, int v2, char op) {
       if(op == '+') return v1+v2;
       if(op == '-') return v1-v2;
       if(op == '*') return v1*v2;
       return 0;
    }

    void parse(string& input, vector<int>& nums, vector<char>& ops) {
        int val = 0;
        for(int i = 0; i < input.size(); ++i) {
            char c = input[i];
            if(isdigit(c)) {
               val = 10*val + (c - '0');
            } else {
               ops.push_back(c);
               nums.push_back(val);
               val = 0;
            }
        }
        nums.push_back(val); //don't forget last one!
    }
};

// Recursive solution using divide and conquer. Final vector is the cartesian product of two sub-vectors

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> numbers;
        vector<char> operators;
        int num = 0;
        for(int i = 0; i < input.size(); i++) {
            char c = input[i];
            if(c >= '0' && c <= '9') num = num*10 + (c-'0');
            else {
                numbers.push_back(num);
                operators.push_back(c);
                num = 0;
            }
        }
        numbers.push_back(num);
        
        int n = numbers.size();
        vector<int> ret;
        eval(numbers, operators, 0, n-1, ret);
        return ret;
    }
    
    void eval(vector<int>& numbers, vector<char>& operators, int lo, int hi, vector<int>& vals) {
        vals.clear();
        if(lo == hi) {
            vals.push_back(numbers[lo]); //only one
            return;
        }
        vector<int> v1, v2;
        for(int mid = lo; mid < hi; ++mid) {
            eval(numbers, operators, lo, mid, v1);
            eval(numbers, operators, mid+1, hi, v2);
            for (int j1 = 0; j1 < v1.size(); ++j1) {
                for(int j2 = 0; j2 < v2.size(); ++j2) {
                    vals.push_back(eval(v1[j1], v2[j2], operators[mid]));
                }
            }
        }
    }
    
    int eval(int n1, int n2, char op) {
        switch (op) {
            case '+': return n1 + n2;
            case '-': return n1 - n2;
            case '*': return n1 * n2;
            default : return 0;
        }
    }
};
