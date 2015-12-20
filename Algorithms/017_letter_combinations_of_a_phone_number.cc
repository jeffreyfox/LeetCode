/*
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer could be in any order you want. 
*/

// Solution 1. Recursive dfs solution. Use a dict storing the conversion rule. Terminate at i == n.
// A variant is also given where termination is at i == n-1.

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> dict = {"", "", "abc", "def", "ghi", "jkl", "mno", "prqs", "tuv", "wxyz"};
        vector<string> result;
        if(digits.empty()) return result;
        int n = digits.size();
        string tmp(n, '0');
        dfs(digits, 0, dict, tmp, result);
        return result;
    }
    //starting from i-th digits
    void dfs(const string& digits, int i, vector<string>& dict, string& tmp, vector<string>& result) {
        if(i == digits.size()) {
            result.push_back(tmp);
            return;
        }
        int idx = digits[i] - '0';
        //choose among possible characters in dict[idx]
        for(auto c : dict[idx]) {
            tmp[i] = c;
            dfs(digits, i+1, dict, tmp, result);
        }
    }
/*  // simplified dfs routine terminating at i == n-1
    void dfs(const string& digits, int i, vector<string>& dict, string& tmp, vector<string>& result) {
        int idx = digits[i] - '0';
        int n = digits.size();
        //choose among possible characters in dict[idx]
        for(auto c : dict[idx]) {
            tmp[i] = c;
            if(i == n-1) result.push_back(tmp);
            else dfs(digits, i+1, dict, tmp, result);
        }
    }
*/
};

