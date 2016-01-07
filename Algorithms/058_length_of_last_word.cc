/*
Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example,
Given s = "Hello World",
return 5. 
*/

// Two pointers, i and j. Scan from right to left
// i is first non-space char, j is first space char after i (right -> left)

class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.size();
        //scan from right end to left, find first non-space character
        int i = n-1;
        while (i >= 0 && s[i] == ' ') i--;
        if (i < 0) return 0;
        //scan from i to left, find first space character
        int j = i;
        while(j >= 0 && s[j] != ' ') j--;
        return i-j;
    }
};
