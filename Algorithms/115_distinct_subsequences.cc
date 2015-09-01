/*
Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3. 
*/

//DP solution, need a 2D vector

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.size(), n = s.size();
        vector<vector<int> > table(m+1, vector<int>(n+1, 0)); //table[i][j]: numDistinct(s[0..i-1], t[0 ..j-1])
        table[0].assign(n+1, 1); //empty string for t
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                table[i][j] = table[i][j-1] + (t[i-1] == s[j-1] ? table[i-1][j-1] : 0);
            }
        }
        return table[m][n];
    }
};
