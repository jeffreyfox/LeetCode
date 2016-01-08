/*
Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT. 
*/

// Solution 1. Subtract and bit-wise shift (*2).
// Need to consider overflow cases.
class Solution {
public:
    int divide(int dividend, int divisor) {
        if(divisor == 0) return INT_MAX;
        if(dividend == 0) return 0;
        if(dividend == INT_MIN) {
            if(divisor == -1) return INT_MAX;
            else if(divisor == 1) return INT_MIN;
        }
        long a = dividend, b = divisor;
        bool neg = (a > 0) ^ (b > 0);
        a = abs(a); b = abs(b);
        int result = 0;
        while(a >= b) {
            long x = b, y = 1;
            while(a >= (x << 1)) {
              x <<= 1; y <<= 1;
            }
            a -= x;
            result += y;
        }
        //result <= INT_MAX
        if(neg) result = -result;
        return result;
    }
};

// Solution 2. Similar one.
class Solution {
public:
    int divide(int dividend, int divisor) {
        long a = dividend, b = divisor;
        a = abs(a); b = abs(b);
        bool negative = (dividend < 0) ^ (divisor < 0);
        // a/b
        long x(b), n(1), ret(0);
        while (x <= a) {
            x <<= 1; n <<= 1;
        }
        //x = n*b and > a
        while (a > 0) {
            while(n > 0 && x > a) { x >>=1; n>>=1; }
            // x <= a or n == 1
            if (n == 0)  break;
            else {
                ret += n;
                a -= x;
            }
        }
        if(negative) return (ret <= long(INT_MAX)+1) ? -ret : INT_MAX;
        else return ret <= INT_MAX ? ret : INT_MAX;
    }
};
