/*
Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

For example, given nums = [-2, 0, 1, 3], and target = 2.

Return 2. Because there are two triplets which sums are less than 2:

[-2, 0, 1]
[-2, 0, 3]

Follow up:
Could you solve it in O(n2) runtime? 
*/

// Two pointers, similar to 3sum.
// Optimization: break if sum is too large.

class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int count = 0;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 0; i < n-2; i++) {
            int res = target - nums[i];
            if(nums[i+1] + nums[i+2] >= res) break;
            int j = i+1, k = n-1;
            while(j < k) {
               if(nums[j] + nums[k] < res) { count += k-j; j++; }
               else k--;
            }
        }
        return count;
    }
};
