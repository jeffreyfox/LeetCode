/*
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.
*/

// A O(k*n) solution.
// For each new number, look further and predict the maximum for the next k steps

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
       int n = nums.size();
       vector<int> ret;
       if(k == 0 || n < k) return ret;
       int m = n-k+1;
       ret.resize(m, INT_MIN);
       //predict the possible maximums according to nums[i]
       for(int i = 0; i < n; ++i) {
          for(int j = max(0, i-k+1); j <= min(i, m-1); ++j) {
             ret[j] = max(ret[j], nums[i]);
          }
       }
       return ret;
    }
};
