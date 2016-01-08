/*
Given an integer n, return the number of trailing zeroes in n!.

Note: Your solution should be in logarithmic time complexity.
*/

// Check how many factors (2 or 5) are contained from 1 to n.
// e.g. n = 100, f = 5
// 5 appears 20 times as 1x5, 2x5 ... 20x5. 
// Then another 4 times from 1 to 20 (when we divide n by 5): 1x5, 2x5, 3x5, 4x5
// Then zero times from 1 to 4(when we divide n by 5).

// Number of trailing zeroes is the minimum of counts of 2s and 5s.
class Solution {
public:
    int trailingZeroes(int n) {
        if(n <= 1) return 0;
        return min(numFact(n, 2), numFact(n, 5));
    }
    //how many factors k do numbers 1 .. n have in total?
    int numFact(int n, int k) {
        int count = 0;
        while(n) {
            n /= k;
            count += n;
        }
        return count;
    }
};
