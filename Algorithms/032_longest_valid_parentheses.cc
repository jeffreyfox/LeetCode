/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4. 
*/

/*
 Dynamic programming, use a table to store the length of longest valid parentheses of s's substring of length i (i = 0 .. n)
 We scan all characters, for i-th character, when we see a ')' we start checking the substring s[0..i-1] of length i. We already know the maximum length of s[0..i), so we check the character before that, if it is '(', then we have found a matching bracket, we further add the part before that '(' is there is any. Be attention of case of possible array out of bound.

  s: 0    ..       j   ...    i-1  i
         [ ... ]  '('   [ ... ]   ')'
*/ 

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if(n <= 1) return 0;
        vector<int> mp(n+1, 0); //mp[n]: the length of lvp substring of s[0..n-1], length n
        int max_len = 0;
        for(int i = 0; i < n; ++i) {
            if(s[i] == ')') {
                int len = mp[i]; //check previous substring
                if(mp[len] >= i || s[i-len-1] != '(') mp[i+1] = 0; //no valid substring ending at s[i]
                else mp[i+1] = len + mp[i-len-1] + 2;
                max_len = max(max_len, mp[i+1]);
            }
        }
        return max_len;
    }
};
