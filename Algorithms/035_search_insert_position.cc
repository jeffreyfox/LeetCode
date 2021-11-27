/*
Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0
*/

// Binary search. Loop invariant:
// nums[0 .. lo-1] < target, nums[hi+1, n) > target, nums[lo, hi] TBD
// If found, return index. If not found, return position lo, because when out of while loop we have lo=hi+1, and target is between nums[hi] and nums[lo].

class Solution {
    
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int lo(0), hi(n-1), mid(0);
        while(lo <= hi) {
            mid = lo + (hi-lo)/2;
            if(target == nums[mid]) return mid;
            if(target < nums[mid]) hi = mid-1;
            else lo = mid+1;
        }
        return lo;
    }
}; 

// Solution using STL lower_bound function.
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    }
};
