/*
Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)
*/

/// O(n) time, O(1) space solution.
/// Two passes, one from left and one from right
/// Product without self = product of all elements to the left, times product of all elements to the right
/// First pass, calculate products of all elements to the left and save it to ret array
/// Second pass, calculate products of all elements to the right, and multiple to the ret array values
/// when done, return the ret array

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, 1);
        int t = 1;
        for (int i = 1; i < n; ++i)
            ret[i] = ret[i-1]*nums[i-1];
        for (int i = n-2; i >= 0; --i) {
            t *= nums[i+1];
            ret[i] *= t;
        }
        return ret;
    }
};

// O(n) time, O(n) space.
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        vector<int> left(n, 1), right(n, 1);
        for (int i = 1; i < n; ++i) {
            left[i] = left[i-1] * nums[i-1];
        }
        for (int i = n-2; i >= 0; --i) {
            right[i] = right[i+1] * nums[i+1];            
        }
        for (int i = 0; i < n; ++i) {
            result[i] = left[i] * right[i];
        }
        return result;
    }
};
