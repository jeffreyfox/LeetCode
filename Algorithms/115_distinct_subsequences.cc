/*
Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3. 
*/

/*
dynamic programming with various possible optimizations

Let dp[i][j] denote number of distinct subsequencies for s[0, i), and t[0, j). Then the distinct subsequency can be constructed from two cases:
a) s[0, j-1) and t[0, j), or, removing s[i-1]
b) s[0, i-1) and t[0, j-1) and if s[i-1] == t[j-1].
Boundary case:
s[i][0] = 1 for all i >= 0, e.g. "" and "", or "ab" and "".
s[0][j] = 0 for all j > 0, e.g. "" and "abc"

1. Scan t as outer loop, use a 2D array. This is less efficient.
2. Scan t as outer loop, use a 1D array and a prev variable. need to properly update prev.

3. Scan s as outer loop, use a 2D array.
4. Scan s as outer loop, use two 1D arrays.
*/

/*
Solution 1. Scan t as outer loop, use a 2D array. This is less efficient.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.size(), n = s.size();
        //outer loop: t, inner loop s
        //dp[i][j]: num-distinct for s[0..j) and t[0..i)
        vector<vector<int> > dp(m+1, vector<int>(n+1, 0));
        for(int j = 0; j <= n; ++j) dp[0][j] = 1;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
               dp[i+1][j+1] = dp[i+1][j] + (t[i] == s[j] ? dp[i][j] : 0);
            }
        }
        return dp[m][n];
    }
};

/*
Solution 2. Scan t as outer loop, use a 1D array and a prev variable. need to properly update prev.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.size(), n = s.size();
        //dp[j] at step i: num-distinct for s[0..j) and t[0..i)
        vector<int> dp(n+1, 1);  //initially 1
        int prev = 0;
        for(int i = 0; i < m; ++i) {
            prev = dp[0];
            dp[0] = 0; //dp[0] means number for t and "", only when t == "", dp[0] = 1, otherwise dp[0] = 0
            for(int j = 0; j < n; ++j) {
               int tmp = dp[j+1];
               dp[j+1] = dp[j] + (t[i] == s[j] ? prev : 0);
               prev = tmp;
            }
        }
        return dp[n];
    }
};

/*
Solution 3. Scan s as outer loop, use a 2D array. can further optimized second loop as j <= min(i, n), but runtime does not get shorter.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<int> > dp(m+1, vector<int>(n+1, 0));
        dp[0][0] = 1;
        for(int i = 1; i <= m; ++i) {
            dp[i][0] = 1;
            for(int j = 1; j <= n; ++j) {
                dp[i][j] = dp[i-1][j] + (s[i-1] == t[j-1] ? dp[i-1][j-1] : 0);
            }
        }
        return dp[m][n];
    }
};

/*
Solution 4. Scan s as outer loop, use two 1D arrays.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<int> dp(n+1, 0), newdp(n+1, 0);
        dp[0] = newdp[0] = 1; //entry 0 is always 1  
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                newdp[j] = dp[j] + (s[i-1] == t[j-1] ? dp[j-1] : 0);
            }
            dp.swap(newdp);
        }
        return dp[n];
    }
};

