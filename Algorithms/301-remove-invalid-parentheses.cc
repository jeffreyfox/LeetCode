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
    
    void backtrack(string s, int i, int j, char c_open, char c_close, vector<string>& result) {
        int count = 0;
        for (; i < s.size(); ++i) {
            if (s[i] == c_open) count++;
            else if (s[i] == c_close) count--;
            if (count < 0) break;
        }        
        if (count < 0) {
            // s[i] is the first excess closing bracket.
            // Consider removing closing brackets from s[j] to s[i].
            for (; j <= i; ++j) {
                if (s[j] != c_close) continue;
                if (j > 1 && s[j] == s[j-1]) continue; // avoids duplicates
                string t = s;
                t.erase(j, 1); // removes s[j]
                // Can't use '(', and ')' explicitly here because the reversed case may also reach here
                // through recursive calls.
                backtrack(t, i, j, c_open, c_close, result);
            }
        } else if (count > 0) {
            // have excess open brackets. Reverse the string and also swap the role of open/close brackets
            // so ')(' is a matching pair.
            string t = s;
            reverse(t.begin(), t.end());            
            // Can use ')', and '(' explicitly here because we won't reach here for the reversed case.
            backtrack(t, 0, 0, c_close, c_open, result);
        } else {
            string t = s;
            if (c_open == ')') reverse(t.begin(), t.end());
            result.push_back(t);
        }
    }
};
