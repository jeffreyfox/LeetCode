/*
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false. 
*/

//Dynamic programming.

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
