/*
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

    Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
    The solution set must not contain duplicate triplets.

    For example, given array S = {-1 0 1 2 -1 -4},

    A solution set is:
    (-1, 0, 1)
    (-1, -1, 2)
*/

/// O(n2) solution
/// Need to consider duplicated entries.
/// Optimization: break if nums[i] > 0, and also num[n-1] < 0 (52ms => 48ms)

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ret;
        int n = nums.size();
        if(n <= 2) return ret;
        vector<int> tmp(3, -1);
        sort(nums.begin(), nums.end());
        if(nums[n-1] < 0) return ret; //no need to continue if largest value is < 0
        for(int i = 0; i < n-2; i++) {
            if(nums[i] > 0) break; //no need to continue if found a positive number
            if(i > 0 && nums[i] == nums[i-1]) continue; //avoid duplicates
            if(nums[i] + nums[i+1] + nums[i+2] > 0) break;
            if(nums[i] + nums[n-2] + nums[n-1] < 0) continue;
            int target = -nums[i];
            int j = i+1, k = n-1;
            while(j < k) {
               int sum = nums[j] + nums[k];
               if(sum < target) j++;
               else if(sum > target) k--;
               else {
                   tmp[0] = nums[i]; tmp[1] = nums[j]; tmp[2] = nums[k];
                   ret.push_back(tmp);
                   j++; k--;
                   while(j < k && nums[j] == nums[j-1]) j++; //avoid duplicates
                   while(j < k && nums[k] == nums[k+1]) k--; //avoid duplicates
               }
            }
        }
        return ret;
    }
};

