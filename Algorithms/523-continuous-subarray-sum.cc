/*
Given an integer array nums and an integer k, return true if nums has a continuous subarray of size at least two whose elements sum up to a multiple of k, or false otherwise.

An integer x is a multiple of k if there exists an integer n such that x = n * k. 0 is always a multiple of k.

 

Example 1:

Input: nums = [23,2,4,6,7], k = 6
Output: true
Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
Example 2:

Input: nums = [23,2,6,4,7], k = 6
Output: true
Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up to 42.
42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.
Example 3:

Input: nums = [23,2,6,4,7], k = 13
Output: false
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
0 <= sum(nums[i]) <= 231 - 1
1 <= k <= 231 - 1
*/

// Keep track of the prefix sum. Use a hash table to track the position of each residue (0 - k-1). Need to perform checks to ensure "at least two".
// Trick: Imagine there is a 0 at the front of the array at index -1.
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (nums.size() == 1) return false;
        unordered_map<int, int> dict;
        dict[0] = -1;
        int sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum = (sum + nums[i]) % k;
            auto iter = dict.find(sum);
            if (iter == dict.end()) dict[sum] = i;
            else if (dict[sum] < i-1) return true; // at least two.
        }
        return false;
    }
};
