/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4. 
*/

/// Dynamic programming, use a table to store the length of longest valid parentheses of s's substring of length i (i = 0 .. n)
/// Use a stack to track the position of '('. When seeing a '(', insert to stack; when seeing a ')', pop stack and find the index of last matching '('.
// Example: say at i we find that the matching bracket is at j. Then len[i+1] = len[j] + i-j+1
//    (  ...  )  ( ... ) 
//           j-1 j     i
//     len[j]     i-j+1

class Solution {
public:
    int longestValidParentheses(string s) {
        if(s.empty()) return 0;
        int max_len = 0;
        int n = s.size();
        deque<int> pos; //stack storing position of '('
        vector<int> len(n+1, 0); //len[i]: max length for the LVP of s[0..i-1] (length of i)
        for(int i = 0; i < n; ++i) {
            if(s[i] == '(') pos.push_back(i);
            else if(!pos.empty()) { //find matching '(' for ')'
                int j = pos.back();
                len[i+1] = len[j] + i-j+1;
                pos.pop_back();
                max_len = max(max_len, len[i+1]);
            }
        }
        return max_len;
    }
};
