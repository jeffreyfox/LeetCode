/*
Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.

For example, given the range [5, 7], you should return 4.
*/


/* If we search from highest bits to lowest bits, the result should have the same bit if m and n have the same bit, 
and once we encountered the first different bit, then all the bits in result on and after this bit should be zero. 
The reason is as follows. Suppose the first different bit is at i, then m[i] should be 0 and n[i] should be 1 (m <=n), 
then the numbers ..011111 and ..100000 should be between m and n, and it will give all zeros after AND operations. 
Thus, the key is to find the highest set bit of m^n, and use ~(m^n-1) as the mask.
Also works for m == n case, where m_and = m, and m_xor = 0, the return value is thus m & ~0 = m & 1111111 = m
*/
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int m_and = m & n;
        int m_xor = m ^ n;
        //mask is the number from highest bit of mask2 minus 1 (i.e. 0011111..)
        int mask;
        while(m_xor) { //each loop removes a rightmost set bit of m_xor
            mask = m_xor-1;
            m_xor = m_xor & mask;
        }
        //after loop, m_xor is 0, and mask is of form 00111..
        return m_and & (~mask);
    }
};

// Solution 2. Shift m and n until they are equal. Record the number of shifts, and shift m back.

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int i = 0;
        while(m != n) {
            i ++;
            m >>= 1;
            n >>= 1;
        }
        return m << i;
    }
};

// Solution 3.
// Alternative solution by shifting bits. For explanations refer to the first solution.

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
