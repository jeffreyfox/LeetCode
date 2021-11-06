/*
Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4]. 
*/

/// Binary search two passes.
/// First find the left-most index with value >= target as lo
/// Then find the right-most index with value <= target as hi
/// Caveat: If lo <= hi, then found the interval, otherwise, not found, return [-1, -1]

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result(2, -1);
        if (nums.empty()) return result;
        
        int lo = 0, hi = nums.size()-1;
        // First find the first element >= target.
        // If search suceeds, lo will be the first element >= target, and hi will be the last element < target, and lo = hi+1
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (nums[mid] < target) lo = mid+1;
            else hi = mid-1;
        }
        result[0] = lo;
        
        // Second find the last element <= target.
        // If search suceeds, lo will be the first element > target, and hi will be the last element <= target, and lo = hi+1
        lo = 0; hi = nums.size()-1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (nums[mid] <= target) lo = mid+1;
            else hi = mid-1;
        }
        result[1] = hi;

        if (result[0] <= result[1]) return result;
        return {-1, -1};
    }
};
