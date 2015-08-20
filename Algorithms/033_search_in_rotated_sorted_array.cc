/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
*/

/// Binary search. The array can be broken into two part, first part is 4-7, second part is 0-2. If array is unrotated, then only first part exists (corner case). 
/// There are three anchor pointings, lo, hi, and mid.
/// First determine whether mid is in first half or second half. Mid is in first half iff nums[mid] >= nums[lo] (we can't use comparison between mid and hi, i.e. nums[mid] > nums[hi] because a corner case where array is not rotated has nums[mid] < nums[hi], but still mid is in first half.

/// If mid is in first half, we know that nums[mid] >= nums[lo], if target falls between the two, then the index has to be between lo and mid.
/// Otherwise, it is between mid and hi.
/// If mid is in second half, we know that nums[mid] <= nums[hi], if target falls between the two, then the index has to be between mid and hi,
/// otherwise, it is between lo and mid.


class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int lo(0), hi(n-1);
        while(lo <= hi) {
            int mid = lo + (hi-lo) / 2;
            if(target == nums[mid]) return mid;
            if (nums[mid] >= nums[lo]) {
                if(target >= nums[lo] && target < nums[mid]) hi = mid - 1;
                else lo = mid + 1;
            } else {
                if(target <= nums[hi] && target > nums[mid]) lo = mid + 1;
                else hi = mid - 1;
            }
        }
        return -1;
    }
};
