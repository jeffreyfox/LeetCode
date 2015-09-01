/*
Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3. 
*/

//DP solution, slightly optimized version (2 1D vectors).

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.size(), n = s.size();
        vector<int> row(n+1, 0), newrow(n+1, 0);
        row.assign(n+1, 1);
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                newrow[j] = newrow[j-1] + (t[i-1] == s[j-1] ? row[j-1] : 0);
            }
            row.swap(newrow);
            newrow[0] = 0; //remember to set first element to zero!
        }
        return row[n];
    }
};
