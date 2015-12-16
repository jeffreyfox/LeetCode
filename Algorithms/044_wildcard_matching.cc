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

/*
See 
https://leetcode.com/discuss/52274/three-solutions-iterative-16ms-180ms-modified-recursion-88ms

Solution 1. Standard DP solution with a 2D vector. Slow.
When we see a '*' it can match nothing, hence dp[i][j-1], or it can match at least one character, hence dp[i-1][j].
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        if(p == "") return s == "";
        //s can be "", p cannot
        int m = s.size(), n = p.size();
        vector<vector<bool> > dp(m+1, vector<bool>(n+1, false)); //match[i][j]: s[0..i-1] matches p[0..j-1]
        dp[0][0] = true; // "" matches ""
        //matching p with ""
        for(int j = 1; j <= n && p[j-1] == '*'; ++j)
            dp[0][j] = true;
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(p[j-1] != '*') dp[i][j] = dp[i-1][j-1] && matchHelper(s[i-1], p[j-1]);
                else dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
        }
        return dp[m][n];
    }

    bool matchHelper(char t, char p) {
        return p == '?' || p == t;
    }
};

/*
Solution 2. Need further analysis
*/

class Solution {
public:
    bool helper(const string &s, const string &p, int si, int pi, int &recLevel)
    {
        int sSize = s.size(), pSize = p.size(), i, curLevel = recLevel;
        bool first=true;
        while(si<sSize && (p[pi]==s[si] || p[pi]=='?')) {++pi; ++si;} //match as many as possible
        if(pi == pSize) return si == sSize; // if p reaches the end, return
        if(p[pi]=='*')
        { // if a star is met
            while(p[++pi]=='*'); //skip all the following stars
            if(pi>=pSize) return true; // if the rest of p are all star, return true
            recLevel++;
            for(i=si; i<sSize; ++i)
            {   // then do recursion
                if(p[pi]!= '?' && p[pi]!=s[i]) continue;
                if(helper(s, p, i+1, pi+1, recLevel)) return true;
                if(recLevel>curLevel+1) return false; // if the currently processed star is not the last one, return
            }
        }
        return false;
    }

    bool isMatch(string s, string p) {
        int recLevel = 0;
        return helper(s, p, 0, 0, recLevel);
    }
};

/*
Solution 3. An elegant greedy solution from Yu's coding garden. Need further study.
*/


