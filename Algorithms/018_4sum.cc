/*
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

    Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
    The solution set must not contain duplicate quadruplets.

    For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

    A solution set is:
    (-1,  0, 0, 1)
    (-2, -1, 1, 2)
    (-2,  0, 0, 2)
*/

// O(n3) solution, need to take care of duplicated entries.
// Also several optimization lines (break/continue).
// Storing partial sums (e.g. nums[n-2] + nums[n-1]) does not reduce run time.

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int> > result;
        vector<int> tmp(4, 0);
        int n = nums.size();
        if(n <= 3) return result;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n-3; ++i) {
            if(i > 0 && nums[i] == nums[i-1]) continue; //avoid duplicates
            if(nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) break;
            if(nums[i] + nums[n-3] + nums[n-2] + nums[n-1] < target) continue;
            for(int j = i+1; j < n-2; ++j) {
                if(j > i+1 && nums[j] == nums[j-1]) continue; //avoid duplicates
                if(nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) break;
                if(nums[i] + nums[j] + nums[n-2] + nums[n-1] < target) continue;
                int k = j+1, l = n-1;
                while(k < l) {
                    int sum = nums[i] + nums[j] + nums[k] + nums[l];
                    if(sum < target) k++;
                    else if(sum > target) l--;
                    else { //equal
                        tmp[0] = nums[i]; tmp[1] = nums[j]; tmp[2] = nums[k]; tmp[3] = nums[l];
                        result.push_back(tmp);
                        k++; l--;
                        while(k < l && nums[k] == nums[k-1]) k++;
                        while(k < l && nums[l] == nums[l+1]) l--;
                    }
                }
            }
        }
        return result;
    }
};
