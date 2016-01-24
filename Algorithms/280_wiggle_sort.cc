/*
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4]. 
*/

// Linear solution:
/* Scan left to right, two passes
 First pass arranges i and i+1 for even i such that nums[i] >= nums[i+1].
 Second pass arranges i and i+1 for odd i such that nums[i] <= nums[i+1].
 In second pass, we could have (i is odd), then we simply swap i and i+1.
               *                   *
           *                 * \  /
        *           =>      /   *
   *                       *
   (i-1 i) (i+1 
*/

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return;
        for(int i = 0; i+1 < n; i += 2) {
            if(nums[i] > nums[i+1])  swap(nums[i], nums[i+1]);
        }
        for(int i = 1; i+1 < n; i += 2) {
            if(nums[i] < nums[i+1])  swap(nums[i], nums[i+1]);
        }
    }
};

// One pass linear solution. We can combine the two passes into one pass.
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return;
        for(int i = 0; i+1 < n; i++) {
            if(!(i & 1) && nums[i] > nums[i+1]) swap(nums[i], nums[i+1]);
            if((i & 1) && nums[i] < nums[i+1]) swap(nums[i], nums[i+1]);
        }
    }
};

// Another O(nlgn) solution using sort. First sort, then swap ajacent pairs.
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return;
        sort(nums.begin(), nums.end());
        for(int i = 1; i+1 < n; i+=2) {
            swap(nums[i] nums[i+1]);
        }
    }
};
