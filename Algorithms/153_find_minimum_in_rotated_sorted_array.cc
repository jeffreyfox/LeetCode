/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.
*/

// 2021. Use nums[0] as pivot. Keep track of minimum seen so far.
class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo = 0, hi = nums.size()-1;
        int result = nums[0];
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            result = min(nums[mid], result);
            if (nums[mid] >= nums[0]) { // left side of array
                lo = mid+1;
            } else {  // right side of array
                hi = mid-1;
            }
        }
        return result;
    }
};

/*
General solution that also works for duplicated cases.
Binary search. The array can be broken into two parts, 
for example, [4 5 6 7 0 1 2], first part is 4-7, second part is 0-2. If array is unrotated, then only first part exists (corner case). 

There are three anchor points, lo, hi, and mid. Compare nums[mid] with nums[hi].
1. If nums[mid] < nums[hi], then the minimum index must be <= mid, so set hi to mid (mid could be the minimum).
2. If nums[mid] > nums[hi], then the array is rorated, and mid is in first part of the sorted array. This means that minimum index > mid, so set lo to mid+1.
   Since nums[mid] > nums[hi], nums[mid] cannot be the minimum, so we can exlude it. 
3. If nums[mid] = nums[hi], we can't say where mid is. It could be left or right. But we can safely exclude nums[hi], since it is a duplicated entry of nums[mid].
   Thus we simply decrement hi. 
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo = 0, hi = nums.size()-1;
        //invariant: [lo, hi] contains minimum
        while (lo < hi) {
            int mid = lo + (hi-lo)/2;
            if (nums[mid] < nums[hi]) hi = mid;
            else if (nums[mid] > nums[hi]) lo = mid+1;
            else hi--;
        }
        return nums[lo];
    }
};
