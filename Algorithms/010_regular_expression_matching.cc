/*
Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
*/

// DP solution.
// When seeing a Ac* when matching B, two cases:
// c* can match empty string, so check whether A matches B
// c* can match one or more c's, so check whether Ac matches B and after B if it matches c

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = p.size(), n = s.size();
        vector<vector<bool> > match(m+1, vector<bool>(n+1, false)); //pattern length i matches text length j?
        match[0][0] = true;
        for(int i = 0; i < m; ++i) { //check p[i]
            if(p[i] == '*') match[i+1][0] = match[i-1][0];
            for(int j = 0; j < n; ++j) {
                if(p[i] != '*')
                    match[i+1][j+1] = match[i][j] && isMatch(s[j], p[i]);
                else   //p[i] = '*'
                    match[i+1][j+1] = match[i-1][j+1] || (match[i+1][j] && isMatch(s[j], p[i-1]));
            }
        }
        return match[m][n];
    }
    bool isMatch(char s, char p) {
        return p == '.' || s == p;
    }
};
