/*
Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
*/

// Scan from left to right, for each character, check if it is in the middle of a palindrome. 
// Consider even and odd cases

class Solution {
public:
    string longestPalindrome(string s) {
        if(s.empty()) return s;
        int n = s.size();
        int istart = 0, max_len = 1;
        for(int i = 0; i < n; ++i) {
            //check odd substrings (j is offset from middle)
            for(int j = 1; j <= i && i+j < n && s[i-j] == s[i+j]; ++j) {
                if(2*j+1 > max_len) { max_len = 2*j+1; istart = i-j; }
            }
            //check even substrings (j is offset from middle)
            for(int j = 1; j <= i+1 && i+j < n && s[i-j+1] == s[i+j]; ++j) {
                if(2*j > max_len) { max_len = 2*j; istart = i-j+1; }
            }
        }
        return s.substr(istart, max_len);
    }
};
