// O(lgn) solution, decode n into binary digits, and calculate x^1, x^2, x^4 procedingly. When the digit is set, add it into the factor.
// e.g:
// n = 13 =   1     1    0     1
//   x^13 = x^8 + x^4 + .. + x^1
// Caveats:
// 1. when n is negative, return 1/ val;
// 2. when x is negative, return negative only when n is odd
// 3. when abs(x) is 1, return 1 (or -1) directly
// 4. maybe overflow?

class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) return 1;
        int sign = (x < 0 && (n & 1)) ? -1 : 1;
        x = abs(x);
        if (x == 1.0) return sign*x;
        bool pos = (n > 0);
        double val = 1.0;
        n = abs(n);
        while (n) {
            if (n & 1) val *= x;
            n >>= 1; x *= x;
        }
        return sign * (pos ? val : 1.0 / val);
    }
};
