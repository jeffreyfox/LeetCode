/*
Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB
*/

/// Iterative solution. Radix-26 notation, can think of 0 as 0, and Z as A0.

class Solution {
public:
    string convertToTitle(int n) {
        string ret;
        while(n) {
            int r = (n - 1) % 26; //r from 0 to 25
            ret = char('A'+r) + ret;
            n = (n - 1) / 26;
        }
        return ret;
    }
};
