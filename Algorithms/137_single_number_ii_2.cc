/*
 Given an array of integers, every element appears three times except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory? 
*/

/// Use bit operations. Extend to general cases (N times)
/// Use an array to store the occurrences of each bit: 
/// count[1] stores whether the bit has been set for AT LEAST 1 times
/// count[2] stores whether the bit has been set for AT LEAST 2 times
/// count[N] stores whether the bit has been set for N times
/// when each bit position has reached maximum number of times (N), we reset the corresponding bit positions in count to zero

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        const int N = 3; //number of times, can be generalized to > 3
        vector<int> count(N+1, 0); //count[i]: occured AT LEAST i times? (count[0] unused)
        for(int i = 0; i < nums.size(); ++i) {
            count[N] = count[N-1] & nums[i];
            for(int n = N-1; n > 1; --n)
                count[n] = (count[n] | (count[n-1] & nums[i])) & ~count[N];
            count[1] = (count[1] | nums[i]) & ~count[N];
        }
        return count[1];
    }
};
