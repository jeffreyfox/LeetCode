/*
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
*/

// Solution using long to store intermediate results. Need to consider integer overflow.
// If y > INT_MAX, then overflow (y should always be positive since it is long and will not overflow), also don't need to check -y < INT_MIN, as it is redundant. (We won't end up with y = 2147483647, since the input x cannot be as large as 7463847412)

class Solution {
public:
    int reverse(int x) {
        int sgn = (x >= 0) ? 1 : -1;
        if (x == 0) return 0;
        if(x == INT_MIN) return 0;
        x = abs(x); // no overflow
        long y = 0;
        while (x) {
            y = y*10 + x%10;
            if(y > INT_MAX) return 0;
            x = x / 10;
        }
        return sgn > 0 ? y : -y;
    }
};

// Solution without using long. Need to consider integer overflow for both addition and mutiplication and abs. 
// check overflow for addition: two positive number adds up to a negative number (y < 0)
// check overflow for multiplication: a > INT_MAX / b
// check overflow for calculating absolute values: x == INT_MIN

// Can combine multiplication and addition overflow check into one. See the next solution.

class Solution {
public:
    int reverse(int x) {
        int sign = x > 0 ? 1 : -1;
        if(x == 0) return 0;
        if(x == INT_MIN) return 0;
        x = abs(x); //no overflow
        int y = 0;
        while(x) {
            if(y > INT_MAX / 10) return 0; //overflow
            y = y*10 + (x%10);
            if(y < 0) return 0; //overflow
            x /= 10;
        }
        y = sign > 0 ? y : -y; //no overflow
        return y;
    }
};

class Solution {
public:
    int reverse(int x) {
        int sign = x > 0 ? 1 : -1;
        if(x == 0) return 0;
        if(x == INT_MIN) return 0;
        x = abs(x); //no overflow
        int y = 0;
        while(x) {
            int r = x % 10;
            if(y > (INT_MAX - r) / 10) return 0; //overflow
            y = y*10 + r;
            x /= 10;
        }
        y = sign > 0 ? y : -y; //no overflow
        return y;
    }
};
