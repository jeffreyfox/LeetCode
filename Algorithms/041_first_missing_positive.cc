/*
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space. 
*/

/* Solution with O(1) space and O(n) time. Uses nums itself as the table. When we find a positive integer i, we should put it in the right position nums[i-1], and put original values there in correct positions as well. This requires a while loop with swap functions. For an array of n numbers, it is guaranteed that the missing positive lies between 1 and n+1. When it is between 1 and n, then at least one entry in nums is not filled properly, and we return that values. When it is n+1, then all entries are filled properly, and we simply return n+1.
Think of indices as mapping nums[i] => i+1.
Scan left to right, only perform swapping when value is within [1 .. N], and the destination does not have correct indices (nums[t-1] != t).s
Caveats:
1. when the destination already has the correct numbers, do not swap. This will avoid an infinite while loop. e.g. 1 1
2. return i+1, n+1.
*/

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        //nums[i] should be i+1
        for(int i = 0; i < n; ++i) {
            int t = nums[i];
            while(t > 0 && t <= n && nums[t-1] != t)
               swap(nums[t-1], t);
        }
        for(int i = 0; i < n; ++i) {
           if(nums[i] != i+1) return i+1;
        }
        return n+1;
    }
};

