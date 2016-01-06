/*
Given an integer, write a function to determine if it is a power of two.
*/

// use bit operations.
// Caveat: need to check if larger than 0!

class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n>0 && !(n&(n-1));
	// return !n && !(n & 0x80000000) && !(n&(n-1))
    }
};
