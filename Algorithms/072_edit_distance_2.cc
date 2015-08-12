/*
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/

//Dynamic programming (space-optimized version). Use two 1D arrays to save space.

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<int> d(n+1, INT_MAX); 
        vector<int> dnew(n+1, INT_MAX); 
        for (int j = 0; j <= n; ++j) d[j] = j;

        for (int i = 1; i <= m; ++i) {  //length i
            for (int j = 0; j <= n; ++j) { //length j
               dnew[j] = d[j] + 1;
               if (j > 0) dnew[j] = min(dnew[j], dnew[j-1]+1);
               if (i > 0 && j > 0) dnew[j] = min(dnew[j], d[j-1] + (word1[i-1] == word2[j-1] ? 0 : 1));
               // if (i > 0) d[i][j] = min(d[i][j], d[i-1][j]+1);
               // if (j > 0) d[i][j] = min(d[i][j], d[i][j-1]+1);
               // if (i > 0 && j > 0) d[i][j] = min(d[i][j], d[i-1][j-1] + (word1[i-1] == word2[j-1] ? 0 : 1));
            }
            d = dnew;
        }
        return d[n];
    }
};
