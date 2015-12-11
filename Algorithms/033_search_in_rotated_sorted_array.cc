/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
*/

/*
Binary search. The array can be broken into two parts, 
for example, [4 5 6 7 0 1 2], first part is 4-7, second part is 0-2. If array is unrotated, then only first part exists (corner case). 
There are three anchor points, lo, hi, and mid.
First determine whether mid is in first half or second half. Mid is in first half iff nums[mid] >= nums[lo] (we can't use comparison between mid and hi, i.e. nums[mid] > nums[hi] because a corner case where array is not rotated has nums[mid] < nums[hi], but still mid is in first half.

1. If mid is in first half, we know that nums[mid] >= nums[lo] (could be equal because mid can be lo, when hi = lo+1), if target falls between the two, then the index has to be between lo and mid. Otherwise, it is between mid and hi.
2. If mid is in second half, we know that nums[mid] <= nums[hi] (could be equal because mid can be hi, when hi = lo), if target falls between the two, then the index has to be between mid and hi. Otherwise, it is between lo and mid.

Difference between finding target and finding minimum:
1. for finding minimum, we let lo < hi, terminate at lo == hi, and return nums[lo]
   for finding target, we let lo <= hi, return as soon as values are found. If not found, terminate at lo > hi.
2. both involve one corner case, where array is not rotated. For find min, just return nums[lo], for search target, we need to carefully design while loop so that it also works for corner cases. Thus we compare nums[mid] and nums[lo], rather than nums[hi]. In find min case, we eliminate corner case upfront, so we compare nums[mid] with nums[hi]. Also, since we could end up mid = lo (when hi and lo differ by one), and nums[lo] will = nums[mid] causing problems, so it is safer to compare with nums[hi].
*/

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
