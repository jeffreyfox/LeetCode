/*
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
*/

// Need to consider integer overflow for both addition and mutiplication and abs. Solution without using long.
// check overflow for addition: two positive number adds up to a negative number (y < 0)
// check overflow for multiplication: a > INT_MAX / b
// check overflow for calculating absolute values: x == INT_MIN

// Can combine multiplication and addition overflow check into one. See the next

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

