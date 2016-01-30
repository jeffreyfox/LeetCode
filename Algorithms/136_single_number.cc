/*
Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory? 
*/

/// Use exclusive OR

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int v = 0;
        for (int i = 0; i < nums.size(); ++i)
            v ^= nums[i];
        return v;
    }
};
