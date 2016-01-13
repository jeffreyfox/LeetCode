/*
A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

click to show spoilers.
Note:

Your solution should be in logarithmic complexity.
*/

// Solution 1. Simple binary search. compare mid with mid+1. break when lo == hi.

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int lo = 0, hi = n-1;
        while(lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if(nums[mid] < nums[mid+1]) lo = mid+1;
            else hi = mid;
        }
        return lo;
    }
};

// Solution 2. Variant of solution 1. Slightly more complicated. Need to compare mid with mid-1 and mid+1.

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        if(n == 1) return 0;
        if(nums[0] > nums[1]) return 0;
        if(nums[n-1] > nums[n-2]) return n-1;
        int lo = 1, hi = n-2;
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            if(nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]) return mid;
            else if(nums[mid] < nums[mid-1]) hi = mid-1;
            else lo = mid+1;
        }
        return lo;
    }
};

