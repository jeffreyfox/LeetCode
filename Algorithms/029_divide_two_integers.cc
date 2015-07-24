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
