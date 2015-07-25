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
