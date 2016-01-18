/*
Implement pow(x, n)
*/

// O(lgn) iterative solution, decode n into binary digits, and calculate x^1, x^2, x^4 procedingly. When the digit is set, add it into the factor.
// e.g:
// n = 13 =   1     1    0     1
//   x^13 = x^8 + x^4 + .. + x^1
// 1. when n is negative, replace n by -n, and x by 1/x
// 2. To avoid overflow, use long instead of int
// 3. shift n towards right one by one.

class Solution {
public:
    double myPow(double x, int n) {
        if(x == 0.0) return 0.0;
        if(n == 0) return 1;
        long m = n;
        if(m < 0) {
            m = -m; x = 1/x;
        }
        //n > 0
        double y = x;
        double res = 1.0;
        while(m) {
            if(m & 1) res *= y;
            m >>= 1;
            y *= y;
        }
        return res;
    }
};

// Solution 2. Similar to above solution, except shift the power of two towards left (avoid overflow!).
class Solution {
public:
    double myPow(double x, int n) {
        if(x == 0.0) return 0.0;
        if(n == 0) return 1;
        bool rev = (n < 0);
        long nn = abs(n);
        double result = 1.0;
        long m = 1;
        double y = x;
        while(m <= nn) {
            if(nn & m) result *= y;
            y *= y; m <<= 1;
        }
        if(rev) result = 1.0/result;
        return result;
    }
};

// Solution 3. Recursive solution. Three cases: n is even, n is positive odd, n is negative odd.
class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) return 1;
        if(n == 1) return x;
        if(n == -1) return 1/x;
        double y = myPow(x, n/2);
        if(n % 2 == 0) return y*y;
        else if(n > 0) return y*y*x;
        else return y*y/x;
    }
};

