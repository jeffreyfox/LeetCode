/*
Related to question Excel Sheet Column Title

Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
*/

// Iterative solution. Just 26-base counting.
// A-Z  : 1 - 26
//   AAA 
//   111 in 26-base counting

class Solution {
public:
    int titleToNumber(string s) {
        int v = 0;
        for(int i = 0; i < s.size(); ++i) {
            v = v*26+(s[i]-'A'+1);
        }
        return v;
    }
};
