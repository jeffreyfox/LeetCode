/*
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Update (2015-02-12):
For C programmers: Try to solve it in-place in O(1) space.

click to show clarification.
Clarification:

    What constitutes a word?
    A sequence of non-space characters constitutes a word.
    Could the input string contain leading or trailing spaces?
    Yes. However, your reversed string should not contain leading or trailing spaces.
    How about multiple spaces between two words?
    Reduce them to a single space in the reversed string.
*/

// Solution: kinda in-place. Procedure:
// 1. remove extra spaces and store the shorted string to s[0, end)
// 2. reverse substring s[0, end)
// 3. reverse individual string in s[0, end)
// Two pointers

class Solution {
public:
    void reverseWords(string &s) {
        if(s.empty()) return;
        int n = s.size();
        //1. remove extra spaces
        //end: end of shorted string, scan j
        int i = 0, j = 0;
        int beg = 0, end = 0;
        while(beg < n && s[beg] == ' ') beg++; 
        //beg points to first non-space char or end
        end = 0; //copy string to start
        for(j = beg; j < n; j++) {
            if(s[j] == ' ') continue;
            else { //non-space character, copy
                if(j > beg && s[j-1] == ' ') s[end++] = ' '; //add space
                s[end++] = s[j];
            }
        }
        //2. reverse substr string s[0, end)
        reverse(s, 0, end);
        
        //3. reverse individual words for s[0, end)
        for(i = 0; i < end; i++) {
            if(s[i] == ' ') continue;
            j = i+1;
            while(j < end && s[j] != ' ') j++;
            reverse(s, i, j); //j points to space or s.end()
            i = j;
        }
        s = s.substr(0, end); //copy result to s (can handle end = 0 case)
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
