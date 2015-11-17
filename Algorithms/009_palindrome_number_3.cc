/*
Determine whether an integer is a palindrome. Do this without extra space.

Some hints:

Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.
*/

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
