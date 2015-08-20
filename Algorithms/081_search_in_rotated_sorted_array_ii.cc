/*
Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/

/// Binary search. The array can be broken into two part, first part is 4-7, second part is 0-2. If array is unrotated, then only first part exists (corner case). 
/// There are three anchor pointings, lo, hi, and mid.
/// First determine whether mid is in first half or second half. Due to duplicated items, we now has three cases:
/// 1. Mid is in first half iff nums[mid] > nums[lo] 
/// 2. Mid is in second half iff nums[mid] < nums[lo]
/// 3. if nums[mid] == nums[lo], we can't say for sure which part mid belongs to, but we know that nums[lo] is not target, so we simply increment lo. 
/// Examples for 3. 
///  2 2 2 2 3 2 2
/// lo    mid   hi  (mid is in first half)
///  2 2 3 2 2 2 2
/// lo    mid   hi  (mid is in second half)
  
/// If mid is in first half, we know that nums[mid] >= nums[lo], if target falls between the two, then the index has to be between lo and mid.
/// Otherwise, it is between mid and hi.
/// If mid is in second half, we know that nums[mid] <= nums[hi], if target falls between the two, then the index has to be between mid and hi,
/// otherwise, it is between lo and mid.


class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int lo(0), hi(n-1);
        while(lo <= hi) {
            int mid = lo + (hi-lo) / 2;
            if(target == nums[mid]) return true;
            if (nums[mid] > nums[lo]) {
                if(target >= nums[lo] && target < nums[mid]) hi = mid -1;
                else lo = mid + 1;
            } else if (nums[mid] < nums[lo]) {
                if(target <= nums[hi] && target > nums[mid]) lo = mid + 1;
                else hi = mid - 1;
            } else {
                lo++;
            }
        }
        return false;
    }
};
