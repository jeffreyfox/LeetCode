/*
Given a string s, return true if the s can be palindrome after deleting at most one character from it.

 

Example 1:

Input: s = "aba"
Output: true
Example 2:

Input: s = "abca"
Output: true
Explanation: You could delete the character 'c'.
Example 3:

Input: s = "abc"
Output: false
 

Constraints:

1 <= s.length <= 105
s consists of lowercase English letters.
*/

class Solution {
public:
    bool validPalindrome(string s) {
        int lo = 0, hi = s.size()-1;
        while (lo < hi) {
            if (s[lo] != s[hi]) return isPalindrome(s, lo, hi-1) || isPalindrome(s, lo+1, hi);
            lo++; hi--;
        }
        return true;
    }
    bool isPalindrome(const string &s, int lo, int hi) {
        while (lo < hi) {
            if (s[lo] != s[hi]) return false;
            lo++; hi--;
        }
        return true;
    }
};
