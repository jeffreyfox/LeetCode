class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t lo = 0x00000001, hi = 0x80000000, XOR = 0;
        uint32_t d = 31;//distance between two bits to be swapped
        while(lo < hi) { //swap two bits
            //XOR has value only at the two bits, other bits are 0
            XOR = (((n & lo ) << d) ^ (n & hi)) | (((n & hi ) >> d) ^ (n & lo));
            n = n ^ XOR; //only two bits are affected, as A ^ 0 = A
            lo = lo << 1;
            hi = hi >> 1;
            d -= 2;
        }
        return n;
    }
};
