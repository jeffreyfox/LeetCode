/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/

// DP solution. Use two variables to track max_include and max_all

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        vector<int> max_inc(n, 0); //maximum value from nums[0..i] including nums[i]
        vector<int> max_all(n, 0); //maximum value from nums[0..i] whether or not including nums[i]
        max_inc[0] = max_all[0] = nums[0];
        max_inc[1] = nums[1]; max_all[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; ++i) {
            max_inc[i] = nums[i] + max_all[i-2];
            max_all[i] = max(max_inc[i], max_all[i-1]);
        }
        return max_all[n-1];
    }
};
