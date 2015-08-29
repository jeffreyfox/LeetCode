/*
Note: This is an extension of House Robber.

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/

/// Use two passes of DP, once excluding nums[0] and once excluding nums[n-1]. Compare the two and return the maximum

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        if(nums.size() == 1) return nums[0];
        int max1 = rob(nums, nums.begin(), nums.end()-1);
        int max2 = rob(nums, nums.begin()+1, nums.end());
        return max(max1, max2);
    }

    int rob(vector<int>& nums, vector<int>::iterator beg, vector<int>::iterator end) {
        int n = end - beg;
        if(n == 0) return 0;
        if(n == 1) return *beg;
        
        vector<int> max_inc(n, 0);
        vector<int> max_all(n, 0);
        max_inc[0] = max_all[0] = *beg;
        max_inc[1] = *(beg+1); max_all[1] = max(*beg, *(beg+1));
        vector<int>::iterator it = beg+2;
        for(int i = 2; i < n; i++, it++) {
            max_inc[i] = max_all[i-2] + *it;
            max_all[i] = max(max_inc[i], max_all[i-1]);
        }
        return max_all[n-1];
    }
};
