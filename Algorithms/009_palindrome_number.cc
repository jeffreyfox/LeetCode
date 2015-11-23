/*
Determine whether an integer is a palindrome. Do this without extra space.

Some hints:

Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.
*/

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

// Another solution without any overflow issue.
// Store a variable mask that is the largest power of 10 smaller or equal to x.
// Then use it as a mask to get the MSD and compare with the LSD. Next time strip off MSD and LSD and repeat, until the two digits meet.

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        //determine minimum power of 10 smaller or equal than x
        int mask = 1;
        int y = x/10;
        while (mask <= y) mask *= 10; 
        while (mask > 1) {
            if (x / mask != x % 10) return false;
            x = (x % mask) / 10; //strip off first and last digit
            mask /= 100; //update mask
        }
        return true;
    }
};

// Another solution by comparing only half digits.

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        if (x == 0) return true;
        int nd = 0; //number of digits of x
        int xx = x;
        while(xx) {
            xx /= 10;
            nd++;
        }
        int y = 0;
        for(int i = 0; i < nd / 2; ++i) {
            y = 10*y + x%10;
            x /= 10;
        }
        if(nd & 1 == 1) x /= 10; //remove additional digit
        return x == y;
    }
};
