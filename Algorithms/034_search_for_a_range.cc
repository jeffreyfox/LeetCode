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
// If lo <= hi, then found the interval
// Otherwise, not found, return (-1, -1)

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ret(2, -1);
        if(nums.empty()) return ret;
        int n = nums.size();
        int lo(0), hi(n-1);
        while(lo <= hi) {
            int mid = lo + (hi-lo)/2;
            if(nums[mid] < target) lo = mid+1;
            else hi = mid-1;
        }
        ret[0] = lo;

        lo = 0, hi = n-1;
        while(lo <= hi) {
            int mid = lo + (hi-lo)/2;
            if(nums[mid] <= target) lo = mid+1;
            else hi = mid-1;
        }
        ret[1] = hi;
        if(ret[0] > ret[1]) ret[0] = ret[1] = -1;
        return ret;
    }
};
