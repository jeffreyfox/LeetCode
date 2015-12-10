/*
Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:

    The order of the result is not important. So in the above example, [5, 3] is also correct.
    Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
*/

// Solution using bit operations. Since the two numbers are different, they should differ by at least one bit position. Say the position is i, then one number should have 0, the other have 1 at this position. We use exlcusive or to find the bits that they differ. Then extract one bit out. And then group the numbers by whether the bit is set or not. We effectively break the problem into two easier problems where each group has only one single number. We calculate the single number for each group separately.

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> result(2, 0);
        int val = 0, n = nums.size();
        for(int i = 0; i < n; ++i) {
            val ^= nums[i];
        }
        //val should be non-zero. Extract one none zero digit.
        val = val & (val ^ (val-1)); //now val has only one digit set
        for(int i = 0; i < n; ++i) {
            if(nums[i] & val) result[0] ^= nums[i];
            else result[1] ^= nums[i];
        }
        return result;
    }
};



