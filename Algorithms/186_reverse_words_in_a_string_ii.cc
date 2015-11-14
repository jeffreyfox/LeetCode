/*
Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.

The input string does not contain leading or trailing spaces and the words are always separated by a single space.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Could you do it in-place without allocating extra space?

Related problem: Rotate Array
*/

// Solution: first reverse the whole string, then scan left to right to reverse each individual words.
// Two pointers.

class Solution {
public:
    void reverseWords(string &s) {
        int n = s.size();
        if(n <= 1) return;
        reverse(s, 0, n);
        int i = 0, j = 0;
        for(int i = 0; i < n;) {
            j = i+1;
            while(j < n && s[j] != ' ') j++;
            reverse(s, i, j); //j points to space
            i = j+1;
        }
    }
    //reverse s[lo, hi)
    void reverse(string &s, int lo, int hi) {
        hi--;
        while(lo < hi) {
            char c = s[lo];
            s[lo] = s[hi];
            s[hi] = c;
            lo++; hi--;
        }
    }
};
