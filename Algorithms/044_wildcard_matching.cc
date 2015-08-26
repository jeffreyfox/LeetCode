/*
Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false
*/

//DP solution, a bit slow

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = p.size(), n = s.size();
        vector<vector<bool> > match(m+1, vector<bool>(n+1, false)); //pattern length i matches text length j?
        match[0][0] = true;
        for(int i = 0; i < m; ++i) { //check p[i]
            if(p[i] == '*') match[i+1][0] = match[i][0];
            for(int j = 0; j < n; ++j) {
                if(p[i] != '*')
                    match[i+1][j+1] = match[i][j] && isMatch(s[j], p[i]);
                else   //p[i] = '*'
                    match[i+1][j+1] = match[i][j+1] || match[i+1][j];
            }
        }
        return match[m][n];
    }
    bool isMatch(char s, char p) {
        return p == '?' || s == p;
    }
};
