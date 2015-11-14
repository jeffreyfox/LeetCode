/*
Given an array of integers, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/

// This version uses insertion sort t sort nums, together with its positions as satellite data. Use two pointers to find the 
// target items, and return their positions. (No hash table is involved)
// Insertion sort: O(n2), search for target: O(n).
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> pos(n);
        for(int i = 0; i < n; ++i) pos[i] = i+1;
        //insertion sort nums
        for(int i = 1; i < n; ++i) {
            int tmp = nums[i];
            int tmp2 = pos[i];
            int j = i-1;
            while(j >= 0 && nums[j] > tmp) {
                nums[j+1] = nums[j]; 
                pos[j+1] = pos[j];
                j--;
            }
            nums[j+1] = tmp;
            pos[j+1] = tmp2;
        }
        
        int l = 0, r = nums.size()-1;
        vector<int> ret(2, 0);
        while(1) {
            int sum = nums[l] + nums[r];
            if(target == sum) {
                ret[0] = min(pos[l], pos[r]), ret[1] = max(pos[l], pos[r]);
                return ret;
            } else if (target > sum) l++;
            else r--;
        }
        return ret;
    }
};
