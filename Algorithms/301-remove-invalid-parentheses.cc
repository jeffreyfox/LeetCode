/*
Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.

Return all the possible results. You may return the answer in any order.

 

Example 1:

Input: s = "()())()"
Output: ["(())()","()()()"]
Example 2:

Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]
Example 3:

Input: s = ")("
Output: [""]
 

Constraints:

1 <= s.length <= 25
s consists of lowercase English letters and parentheses '(' and ')'.
There will be at most 20 parentheses in s.
*/

// References:
// https://leetcode.com/problems/remove-invalid-parentheses/discuss/75027/Easy-Short-Concise-and-Fast-Java-DFS-3-ms-solution
// https://www.youtube.com/watch?v=lEMDEmQje1Q&t=0s

// Scan the string from left to right.
// 1. When seeing an excess ')', remove one '(' in the preceeding characters and recurse.
// 2. When scanning to the end and see more '('s, reverse the string, and reverse the role of open/close brackets so ')(' is a matched bracket pair.
// Note that when recursing on the first case, the front pointer points to the next character to be examined. The back pointer points to the position where s[0..back) is
// already matched and thus should be excluded from future considerations. Also, we should pass c_open and c_close to the recursive function, not '(', ')' explicity.
// Because case 2 may also reach here through recursive calls.

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> result;
        backtrack(s, 0, 0, '(', ')', result);
        return result;
    }
    
    void backtrack(string s, int left, int right, char c_open, char c_close, vector<string>& result) {
        int count = 0;
        int n = s.size();
        for (; right < n; ++right) {
            if (s[right] == c_open) count++;
            else if (s[right] == c_close) count--;
            if (count < 0) break;
        }
        if (count < 0) {
            for (; left <= right; ++left) {
                if (s[left] != c_close) continue;
                if (left > 1 && s[left] == s[left-1]) continue;
                string t = s;
                t.erase(left, 1);
                backtrack(t, left, right, c_open, c_close, result);
            }
        } else if (count > 0) {
            string t = s;
            reverse(t.begin(), t.end());
            backtrack(t, 0, 0, ')', '(', result);
        } else {
            string t = s;
            if (c_open == ')') reverse(t.begin(), t.end());
            result.push_back(t);
        }
    }
};
