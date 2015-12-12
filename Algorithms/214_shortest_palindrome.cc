/*
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".
*/

//Solution 1. O(n2) solution results in TLE.
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        if(n <= 1) return s;
        int i = 0, j = 0;
        int max_len = 1; //max length palindrome substring s[0.. max_len-1]
        for(i = (n-1)/2; i >= 0; --i) { //search first half only
            //check even case: [i-j .. i i+1 .. i+j+1]
            for(j = 0; i-j >= 0 && s[i-j] == s[i+j+1]; ++j) ;
            if(j == i+1) { max_len = 2*j; break; }
            
            //check odd case: [i-j .. i .. i+j]
            for(j = 0; i - j >= 0 && s[i-j] == s[i+j]; ++j) ;
            if(j == i+1) { max_len = 2*j-1; break; }
        }
        string result;
        for(int k = n-1; k >= max_len; --k) {
            result.push_back(s[k]);
        }
        result += s;
        return result;
    }
};

/*
Solution 2. KMP algorithm. Text is reverse of s, pattern is s, search s in t, and find the last j position before exit. j is the length of the longest palindrome substring.
e.g.
s = aacecaaa
text    = aaacecaa
pattern = aacecaaa
after KMP, we end up with
    01234567
    aaacecaa
     aacecaaa
            j = 7, => lps = "aacecaa"
*/  

class Solution {
public:
    string shortestPalindrome(string s) {
       int n = s.size();
        if(n <= 1) return s;
        string t = s; //text to search, reverse of s
        reverse(t.begin(), t.end());
        //s is pattern
        vector<int> f(n+1, -1); //transfer function
        int k = -1;
        for(int j = 1; j <= n; ++j) {
            while(k >= 0 && s[k] != s[j-1]) k = f[k];
            f[j] = ++k;
        }
        //now start matching
        int i(0), j(0);
        while(i < n && j < n) {
            if(t[i] == s[j]) { i++; j++; } 
            else if(j == 0) i++;
            else j = f[j];
        }
        //previous j characters matched
        if(j == n) return s;
        else return t.substr(0, n-j) + s;
    }
};

