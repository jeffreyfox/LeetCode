// Need to take care of integer overflow
class Solution {
public:
    int reverse(int x) {
        int sgn = (x >= 0) ? 1 : -1;
        if (x == 0) return 0;
        unsigned y = abs(x); // no overflow
        long z = 0;
        while (y) {
            int r = y % 10;
            y = y / 10;
            long nz = z*10 + r;
            if (nz < z) return 0; //overflow
            z = nz;
        }
        if (sgn == 1 && z > INT_MAX) return 0; //overflow
        if (sgn == -1 && z > long(INT_MAX) + 1) return 0; //overflow
        return sgn*z;
    }
};

