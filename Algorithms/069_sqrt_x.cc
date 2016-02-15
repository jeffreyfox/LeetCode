/*
Implement int sqrt(int x).

Compute and return the square root of x.
*/

/// Binary search. Loop invariant:
/// [1 .. lo-1]: < sqrt(x)
/// [lo .. hi]: to be checked
/// [hi+1, x]: > sqrt(x)
/// Need to take care of possible overflow (mid > INT_MAX / mid)

class Solution {
public:
    int mySqrt(int x) {
        if (x <= 0) return 0;
        int lo = 1, hi = x, mid = 0;
        while(lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (mid > INT_MAX / mid) hi = mid - 1;
            else {
                int v = mid * mid;
                if (v < x) lo = mid + 1;
                else if (v > x) hi = mid - 1;
                else return mid;
            }
        }
        return hi;
    }
};

// Another solution using long to avoid overflow
class Solution {
public:
    int mySqrt(int x) {
       if(x <= 0) return 0;
       if(x == 1) return 1;
       long xx = x;
       int lo = 1, hi = x-1;
       //(lo-1)*(lo-1) <= x, (hi+1)*(hi+1) > x, hi*hi
       while(lo <= hi) {
           long mid = lo + (hi-lo)/2;
           long val = mid*mid;
           if(val == x) return mid;
           else if(val < x) lo = mid+1;
           else hi = mid-1;
       }
       return hi;
    }
};

// Solution 3. Newton's iteration
// For given x, solve f(y) = y*y - x = 0
// Then y_(n+1) = y_n - f(y)'/f(y) = 0.5*(y_n + x/y_n)
// exit when converges (two consecutive y's differ by some amount)

class Solution {
public:
    int mySqrt(int x) {
        if(x <= 0) return 0;
        double y = x, yold = 0;
        while(fabs(y-yold) > 0.1) {
            yold = y;
            y = 0.5*(y + x/y);
        }
        return y;
    }
};
