// Another solution without any overflow issue.
// Store a variable hi that is the largest power of 10 smaller or equal to x.
// Then use it as a mask to get the MSD and compare with the LSD. Next time strip off MSD and LSD and repeat, until the two digits meet.

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        //determine minimum 100..00 smaller or equal than x
        int hi = 1;
        while (x / hi >= 10) hi *= 10; 
        // x = 236632 => hi = 100000
        while (hi > 1) {
            if (x / hi != x % 10) return false;
            x = (x % hi) / 10; //strip off first and last digit
            hi /= 100; //update mask
        }
        return true;
    }
};
