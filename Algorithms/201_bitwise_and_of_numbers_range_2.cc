/* Alternative solution by shifting bits. For explanations refer to the first solution */

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        if(m == n || n == 0) return n;
        int ret = 0;
        unsigned int i = 0x80000000; //1000...
        while(i) {
            if ((m ^ n) & i) break; //m and n's bits differ at that bit
            else ret = ret | (m & i); //bit the same, copy m's bit to result
            i >>= 1; //move one bit lower
        }
        return ret;
    }
};
