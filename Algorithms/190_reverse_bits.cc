/*
Reverse bits of a given 32 bits unsigned integer.

For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).

Follow up:
If this function is called many times, how would you optimize it?

Related problem: Reverse Integer
*/

// Solution 1. Similar to reverse integer. Get last digit and shift the original number to right, and new number left:
// 123, 0 => 3, 12 => 32, 1 => 321, 0
// Optimization: when the original number is zero, stop the for loop and shift the number by the proper amount.

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        if(n == 0) return 0;
        uint32_t m = 0;
        for(int i = 0; i < 32; ++i) {
            m = (m << 1) | (n & 1);
            n >>= 1;
            if(n == 0) return m << (31-i);
        }
        return m;
    }
};

// Solution 2 using exclusive or.

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

// Solution 3. Swap in groups.
// For 8 bit number, need 3 passes. For 32 bit, 5 passes.
// [1 2 3 4]-[5 6 7 8] => 5 6 7 8 1 2 3 4
// [5 6]-[7 8] [1 2]-[3 4] => 7 8 5 6 3 4 1 2
// [7]-[8] [5]-[6] [3]-[4] [1]-[2] => 8 7 6 5 4 3 2 1

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        n = ((n & 0xFFFF0000) >> 16) | ((n & 0x0000FFFF) << 16);
        n = ((n & 0xFF00FF00) >>  8) | ((n & 0x00FF00FF) <<  8);
        n = ((n & 0xF0F0F0F0) >>  4) | ((n & 0x0F0F0F0F) <<  4);
        n = ((n & 0xCCCCCCCC) >>  2) | ((n & 0x33333333) <<  2);
        n = ((n & 0xAAAAAAAA) >>  1) | ((n & 0x55555555) <<  1);
        return n;
    }
};

