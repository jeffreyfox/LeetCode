/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/

// DP solution, use one vector max_all, whose i-th entry means the maximum amount for robbing houses 0 to i.
// Recursive formula:
// max_all[i] = max of the following two cases:
// including i-th house, then i-1 should be excluded, thus: max_all[i-2] + nums[i]
// excluding i-th house, then no requirements on i-1, thus: max_all[i-1]

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        vector<int> max_all(n, 0); //maximum value from nums[0..i]
        max_all[0] = nums[0];
        max_all[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; ++i) {
            max_all[i] = max(max_all[i-2] + nums[i], max_all[i-1]);
        }
        return max_all[n-1];
    }
};

// Optimized solution, since we only need the last two values for max_all, we can save the space by using two variables
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        int lastlast = nums[0];
        int last = max(nums[0], nums[1]);
        int curr = 0;
        for (int i = 2; i < n; ++i) {
            curr = max(lastlast + nums[i], last);
            lastlast = last; last = curr;
        }
        return curr;
    }
};

// Old DP solution. Use two variables to track max_include and max_all

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
