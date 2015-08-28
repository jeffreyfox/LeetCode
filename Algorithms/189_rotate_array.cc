/*
Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.

[show hint]
Hint:
Could you do it in-place with O(1) extra space?

Related problem: Reverse Words in a String II
*/

// Reverse method

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k = k % n;
        if(k == 0) return;
        reverse(nums, 0, n);
        reverse(nums, 0, k);
        reverse(nums, k, n);
    }
    //reverse nums[beg, end)
    void reverse(vector<int>& nums, int beg, int end) {
        int len = end-beg;
        for (int lo = beg, hi = end-1; lo < hi; lo++, hi--) {
            int t = nums[lo];
            nums[lo] = nums[hi];
            nums[hi] = t;
        }
    }
};
