/*
Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

click to show more practice.
More practice:

If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).
*/

/// Solution 1: sliding window. Move one step further to optimize. O(n)

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int sum = 0, minL = INT_MAX;
        for(int i = 0, istart = 0; i < n; ++i) {
            sum += nums[i];
            if(sum < s) continue;
            while(sum - nums[istart] >= s) {
                sum -= nums[istart++];
            }
            minL = min(minL, i-istart+1);
            sum -= nums[istart++]; //move one step further
        }
        return minL != INT_MAX ? minL : 0;
    }
};

/// Solution 2: binary search on the accumulative sums. O(nlogn)
// First create the partial sum array, then scan the sum, if the paritial_sum >= s, then we search for the array before the element and find the largest element <= (partial_sum - s). Use binary search
// Since all numbers are positive, if we see partial_sum == s, we can skip the binary search and use i+1 as the length (can't be shorter than nums[0..i].

/// So far, divide and conquer seems not possible...

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.empty()) return 0;
        //get partial sums
        int n = nums.size();
        vector<int> partial(n, 0);
        partial[0] = nums[0];
        int minL = INT_MAX;
        for(int i = 1; i < n; ++i) {
            partial[i] = partial[i-1] + nums[i];
        }
        for(int i = 0; i < n; ++i) {
            if(partial[i] >= s) {
                //binary search for largest number <= residue in sums[0, i-1];
                int residue = partial[i] - s;
                int lo = 0, hi = i-1, mid = 0;
                while(lo <= hi) {
                    mid = lo + (hi - lo) / 2;
                    if(partial[mid] <= residue) lo = mid+1;
                    else hi = mid-1;
                }
                minL = min(minL, i-hi);
            }
        }
        return minL == INT_MAX ? 0 : minL;
    }
};

