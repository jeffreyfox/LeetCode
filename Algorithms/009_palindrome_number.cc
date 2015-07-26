// Most straightforward solution: construct the reverse number from x, and compare with x
// Doesn't handle overflow explicitly because when overflow happens, y != x

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int y = 0, num = x;
        while (num > 0) {
            y = y * 10 + num % 10;
            num /= 10;
        }
        return y == x;
    }
};
