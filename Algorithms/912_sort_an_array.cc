/*
Given an array of integers nums, sort the array in ascending order.

Example 1:

Input: nums = [5,2,3,1]
Output: [1,2,3,5]

Example 2:

Input: nums = [5,1,1,2,0,0]
Output: [0,0,1,1,2,5] 

Constraints:

    1 <= nums.length <= 5 * 104
    -5 * 104 <= nums[i] <= 5 * 104
*/

// Solution using counting sort because the values lie in a range comparable to n. Time complexity O(n). Space complexity O(n) as it needs 2 additional vectors.
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        vector<int> counts(kMax, 0);
        // Construct counts
        for (const int num : nums) {
            counts[num + kOffset] ++;
        }
        // Accumulate
        for (int i = 1; i < kMax; ++i) {
            counts[i] += counts[i-1];
        }
        // Put integers into the correct location
        vector<int> result(nums.size());
        for (int k = nums.size()-1; k >= 0; --k) {
            int idx = --counts[nums[k] + kOffset];
            result[idx] = nums[k];
        }
        return result;
    }
    
private:
    const int kMax = 100'001;
    const int kOffset = 50'000;
};
      
