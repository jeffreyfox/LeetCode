// Newton's iteration
// For given x, solve f(y) = y*y - x = 0
// Then y_(n+1) = y_n - f(y)'/f(y) = 0.5*(y_n + x/y_n)
// exit when converges (two consecutive y's differ by some amount)

class Solution {
public:
    int mySqrt(int x) {
        if (x <= 0) return 0;
        double y = x, yy = 0;
        while(fabs(y - yy) > 0.5) {
            yy = y;
            y = .5*(y + x / y);
        }
        return y;
    }
};
