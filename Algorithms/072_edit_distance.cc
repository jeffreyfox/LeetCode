/*
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/

/*
https://leetcode.com/discuss/43398/20ms-detailed-explained-c-solutions-o-n-space
*/

/*
Classic dynamic programing, classical solution using a 2-D matrix.
Consider boundary cases.
The matrix dp[i][j] means the edit distance for s[0, i) and t[0, j), excluding the last character. Here i and j means the length, not the index for the ending string.
so to calculate dp[i][j] we need information for s[i-1] and t[j-1].
For boundary cases:
dp[i][0] = i because changing length-i string to empty string requires i operations. Here we see the convenience of using length as dp's index variable.

We can first write two separate routines for boundary cases i = 0 and j = 0, and then write a nested loop for i >=1 and j >= 1. We can also put them in one loop and take care of boundary cases in if statements.
*/

//Solution 1. Use a 2D array storing the min edit distance between the prefixes of word1 and word2

class Solution {
public:
    int minDistance(string word1, string word2) {
        if(word1.empty()) return word2.size();
        if(word2.empty()) return word1.size();
        int m = word1.size(), n = word2.size();
        vector<vector<int> > dp(m+1, vector<int>(n+1, INT_MAX)); //dp[i][j]: min-distance between word1[0, i) and word2[0, j)
        for(int i = 0; i <= m; ++i) dp[i][0] = i;
        for(int j = 0; j <= n; ++j) dp[0][j] = j;
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                dp[i][j] = min(dp[i-1][j]+1, dp[i][j-1]+1);
                dp[i][j] = min(dp[i][j], dp[i-1][j-1] + (word1[i-1] != word2[j-1]));
            }
        }
        return dp[m][n];
    }
};

/*
Space optimized solution. Because we only need dp[i-1][j], dp[i][j-1] and dp[i-1][j-1] to calcualte dp[i][j], we can use two 1D arrays. cur and next. After each row we swap cur and next.

A even better optimized solution is to use one array curr, and use a temporary variable to store dp[i-1][j-1]. Before updating cur[i], its old value corresponds to dp[i-1][j], and the already updated value in cur[i-1] corresponds to dp[i][j-1]. The key is to find dp[i-1][j-1]. If every step before overwriting cur[i], we store it in a variable pre, so next step (j = j+1) the pre value is exactly dp[i-1][j-1]!. The additional work is to update pre at the current step, we do this by first storing the old cur[j] value in a variable tmp, and in the end assign it to pre.

A final optimization is that, when we see two characters are equal, e.g.
abe cde, we immediately get minD(abe, cde) = minD(ab, cd), instead of doing the minimum among
minD(abe, cd)+1, minD(ab, cde)+1, and minD(ab,cd).
The reason is that we know ajacent entries in the table can only differ by one. i.e. fabs(dp[i+1][j] - dp[i][j]) <= 1. so minD(ab, cd) <= minD(ab,cde)+1, and minD(ab, cd) is guaranteed to be the minimum among the three
For example:
dp(acb, ab) = dp(ac, ab) = 1
dp(acb, ad) = dp(ac, ad) + 1
*/

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<int> dp(n+1, INT_MAX);
        int pre = 0;
        //i = 0 case
        for(int j = 0; j <= n; ++j) dp[j] = j;

        for(int i = 1; i <= m; ++i) {
            pre = dp[0];
            dp[0] = i;
            for(int j = 1; j <= n; ++j) {
                if (word1[i-1] == word2[j-1]) {  //equal case
                    int tmp = dp[j];
                    dp[j] = pre;
                    pre = tmp;
                } else  {
                    int tmp = dp[j];
                    dp[j] = min(min(dp[j]+1, dp[j-1]+1), pre+1);
                    pre = tmp;
                }
            }
        }
        return dp[n];
    }
};
