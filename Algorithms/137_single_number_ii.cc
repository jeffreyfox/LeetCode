/*
Given an array of integers, every element appears three times except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory? 
*/

/// Use bit operations. Can extend to general cases (N times)
/// Use three variables to store the occurrences of each bit: 
/// ones stores whether the bit has been set for AT LEAST 1 times
/// twos stores whether the bit has been set for AT LEAST 2 times
/// threes stores whether the bit has been set for 3 times
/// when each bit position has reached maximum number of times (3), we reset the corresponding bit positions in ones and twos to zero

/// The "AT LEAST" implies that the ones, twos are not mutually exclusive (e.g. ones & twos != 0)

// 1. A given bit position has appeared 3 times iff already appeared 2 times AND the corresponding bit of nums[i] is set, hence: threes = twos & nums[i]
// 2. For twos, if it is already set (appeared at least 2 times), we don’t touch it, otherwise, it can be set to 1 iff it has appeared at least one time and nums[i] has the bit set, hence twos = twos | (ones & nums[i]). 
// 3. For ones, if it is already set (appeared at least 1 times), we don’t touch it, otherwise, it can be set to 1 iff nums[i] has the bit set, hence ones = ones | nums[i]. 
// 4. For both twos and ones, we need to reset bits when reaching 3 times. Thus: ones = ones & ~threes; twos = twos & ~threes;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ones(0), twos(0), threes(0);
        for(int i = 0; i < nums.size(); ++i) {
            threes = twos & nums[i];
            twos = (twos | (ones & nums[i])) & ~threes;
            ones = (ones | nums[i]) & ~threes; // it is |, not ^
        }
        return ones;
    }
};

// Extension to general cases (N times)
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
