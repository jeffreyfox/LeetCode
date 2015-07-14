// use bit operations (check again 0 and INT_MIN 10000000..)
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n>0 && !(n&(n-1));
	// return !n && !(n & 0x80000000) && !(n&(n-1))
    }
};
