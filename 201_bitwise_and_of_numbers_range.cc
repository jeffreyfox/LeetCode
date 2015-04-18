/* If we search from highest bits to lowest bits, the result should have the same bit if m and n have the same bit, and once we encountered the first different bit, then all the bits in result on and after this bit should be zero. The reason is as follows. Suppose the first different bit is at i, then m[i] should be 0 and n[i] should be 1 (m <=n), then the numbers ..011111 and ..100000 should be between m and n, and it will give all zeros after AND operations. Thus, the key is to find the highest set bit of m^n, and use ~(m^n-1) as the mask.
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
