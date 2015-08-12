/*
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/

//Dynamic programming. Use a 2D array storing the min edit distance between the prefixes of word1 and word2

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int> > d(m+1, vector<int>(n+1, INT_MAX)); //d[i][j]: edit distance from word1's length-i prefix to word2's length-j prefix
        d[0][0] = 0;
        for (int i = 0; i <= m; ++i) {  //length i
            for (int j = 0; j <= n; ++j) { //length j
                if (i > 0) d[i][j] = min(d[i][j], d[i-1][j]+1);
                if (j > 0) d[i][j] = min(d[i][j], d[i][j-1]+1);
                if (i > 0 && j > 0) d[i][j] = min(d[i][j], d[i-1][j-1] + (word1[i-1] == word2[j-1] ? 0 : 1));
            }
        }
        return d[m][n];
    }
};
