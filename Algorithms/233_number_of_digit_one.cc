/*
Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

For example:
Given n = 13,
Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.

Hint:

Beware of overflow.
*/

// Count the occurrences of 1 on each digit seperately, and sum them up.
// First observe that for any number starting with a one on digit i, there are 10^i of them, e.g. i = 2, 100-199 (count = 100)
// For an arbitrary number, let's determine how many times the number of 1s appear at digit i, 
// let the number formed to the left of d as l, and to the right of d as r. For example: 264d32, where d can be 0 to 9.
// and l = 27, r = 32.
// (1) if d = 0, then n = 27032. The numbers contributing are from 001xx to 261xx, a total of 27*100,
//     or in general, l*10^i.
// (2) if d = 1, then n = 27132, The numbers contributing are from 001xx to 261xx, plus 27100 to 27132, a total of 27*100 + 33,
//     or in genera, l*10^i + r+1
// (3) if d > 1, e.g. n = 27232. The numbers contributing are from 001xx to 271xx, a total of (27+1)*100,
//     or in genera, (l+1)*10^i
// Algorithm starts from least significant digit, and store and update the 10^i value.

class Solution {
public:
    int countDigitOne(int n) {
        if (n <= 0) return 0;
        int ndigit = 0;
        int x = n;
        while (x) {
            x /= 10; ndigit ++;
        }
        int count = 0;
        int power = 1;
        for (int i = 0; i < ndigit; ++i) { //starting from least digit to most
            int d = n / power % 10; // digit
            int l = n / power / 10; //number to the left of d
            int r = n % power; //number to the right of d
            if (d == 0) count += l*power;
            else if (d == 1) count += l*power + r+1;
            else count += (l+1)*power;
            power *= 10;
        }
        return count;
    }
};
