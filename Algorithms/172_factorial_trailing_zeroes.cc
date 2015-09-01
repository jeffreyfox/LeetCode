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
        int twos = numFactors(n, 2);
        int fives = numFactors(n, 5);
        return min(twos, fives);
    }
    int numFactors(int n, int f) {
        if(n <= 0) return 0;
        int cnt = 0;
        while(n) {
            n /= f;
            cnt += n;
        }
        return cnt;
    }
};
