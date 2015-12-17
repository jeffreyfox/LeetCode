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

/*
Iterative solution. Radix-26 notation, can think of 0 as 0, and Z as A0.
remember to subtract 1.
 ABCD = 1*26^3 + 2*26^2 + 3*26 + 26, 
 ZZZZ = 26*26^3 + 26*26^2 + 26*26 + 26, 
The ZZZZ case, we can not just do / 26, because Z is just 26. But we can do -1, so to extract the last Z, we subtract one from the number, then the last number becomes 25, so when we do % 26, we end up wiht 25. Similarly, when we strip off the last Z, we can't just do / 26, since the last Z will give a 1, we can subtract one, and we are left with 26*26^2 + 26*26 + 26, which is just ZZZ.
*/

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
