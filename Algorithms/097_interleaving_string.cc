/*
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false. 
*/

/*
Dynamic programming.
Use a 2D array recording whether s1[0, i) and s2[0, j) interleaves to form s3[0, i+j).

If dp[i][j] is true, it can be either of the two cases:
dp[i-1][j] is true and s1[i-1] == s3[i+j-1]
1)
adb | e
a b
  d   | e 

2).
a d e |b
  a  | b
 d e

Boundary cse: i = 0 or j = 0.
we further define dp[0][0] = 0.

We can put boundary condition in various places (either outside main loop, or inside)
*/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if(n1+n2 != n3) return false;
        //table[i][j]: s3[0 .. i+j-1] is interleaved by s1[0..i-1] and s2[0 .. j-1]
        vector<vector<bool> > table(n1+1, vector<bool>(n2+1, false));
        table[0][0] = true;
        for (int i = 0; i < n1 && s1[i] == s3[i]; ++i) {
            table[i+1][0] = true; //only uses s1
        }
        for (int j = 0; j < n2 && s2[j] == s3[j]; ++j) {
            table[0][j+1] = true; //only uses s2
        }
        for (int i = 0; i < n1; ++i) { //check s1[i]
            for (int j = 0; j < n2; ++j) { //check s2[j]
                table[i+1][j+1] = (s3[i+j+1] == s2[j] && table[i+1][j]) ||
                                  (s3[i+j+1] == s1[i] && table[i][j+1]);
            }
        }
        return table[n1][n2];
    }
};

/* Slightly optimized solution still using 2D array. Use length as outer loop. Avoid unecessary checks. 4ms. */

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.empty()) return s2 == s3;
        if(s2.empty()) return s1 == s3;
        int m = s1.size(), n = s2.size(), p = s3.size();
        if(m + n != p) return false;
        vector<vector<bool> > dp(m+1, vector<bool>(n+1, false)); //dp[i][j], whether s1[0 .. i) and s2[0 .. j) interleaves to form s3[0 .. i+j).
        dp[0][0] = true;
        for(int len = 1; len <= p; ++len) { //determine s3[0, len), check s3[0, len-1) and s3[len-1]
            bool found = false;
            for(int i = 0; i <= min(len-1, m); ++i) { //checking s1[0, i) and s1[i]
                int j = len - i-1; //checking s2[0, j) and s2[j]
                if(dp[i][j]) {
                    if(s1[i] == s3[len-1]) found = dp[i+1][j] = true; 
                    if(s2[j] == s3[len-1]) found = dp[i][j+1] = true;
                }
            }
            if(!found) return false;
        }
        return dp[m][n];
    }
};

/*
Space optimized version: only a 1D array (8ms).
*/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.empty()) return s2 == s3;
        if(s2.empty()) return s1 == s3;
        int m = s1.size(), n = s2.size(), p = s3.size();
        if(m + n != p) return false;
        vector<bool> dp(n+1, false); //dp[i][j], whether s1[0 .. i) and s2[0 .. j) interleaves to form s3[0 .. i+j).
        dp[0] = true;
        for(int j = 1; j <= n; ++j) {
            dp[j] = dp[j-1] && (s2[j-1] == s3[j-1]);
        }
        
        for(int i = 1; i <= m; ++i) { //checking s1[0, i)
            dp[0] = dp[0] && (s1[i-1] == s3[i-1]);
            for(int j = 1; j <= n; ++j) { //checking s2[0, j)
                dp[j] = (dp[j] && (s1[i-1] == s3[i+j-1])) ||
                            (dp[j-1] && (s2[j-1] == s3[i+j-1]));
            }
        }
        return dp[n];
    }
};

