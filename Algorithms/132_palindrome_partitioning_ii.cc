/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut. 
*/

// Dynamic programming.

class Solution {
public:
    int minCut(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        vector<int> minCuts(n+1, INT_MAX); //min-cuts for s's length-i prefix (i = 0 .. n)
        minCuts[0] = -1; minCuts[1] = 0; // define minCut for empty string as -1 for later convenience
        for (int i = 0; i < n; ++i) { //check s[i]
            //could s[i] be in the middle of odd-length palindrome?
            for (int j = 0; i >= j && i+j < n && s[i-j] == s[i+j]; ++j) //j = 0 is needed to init minCuts[i+1]
                minCuts[i+j+1] = min(minCuts[i+j+1], minCuts[i-j]+1);
            //could s[i] be in the middle of even-length palindrome?
            for (int j = 0; i >= j && i+j+1 < n && s[i-j] == s[i+j+1]; ++j)
                minCuts[i+j+2] = min(minCuts[i+j+2], minCuts[i-j]+1);
        }
        return minCuts[n];
    }
};
