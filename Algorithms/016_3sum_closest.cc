/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

/// O(n2) solution

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int result = 0;
        int min_diff = INT_MAX;
        int n = nums.size();
        if(n <= 2) return 0;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n-2; ++i) {
            if(i > 1 && nums[i] == nums[i-1]) continue;
            int j = i+1, k = n-1;
            while(j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                int diff = target - sum;
                if(diff == 0) return target;
                else if(diff < 0) k--;
                else j++;
                if(abs(diff) < min_diff) {
                    min_diff = abs(diff);
                    result = sum;
                }
            }
        }
        return result;
    }
};
