// Generate permutation sequence in lexigraphical order
// start from previous permutation, perform swap/reverse operations to get the next premutation
// Algorithm (from wikipedia):
// 1. Find the largest index k such that a[k] < a[k + 1]. If no such index exists, the permutation is the last permutation.
// 2. Find the largest index l greater than k such that a[k] < a[l].
// 3. Swap the value of a[k] with that of a[l].
// 4. Reverse the sequence from a[k + 1] up to and including the final element.
// Even works for cases where array has duplicated entries (will only output unique entries once)

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        //find largest k such that nums[k] < nums[k+1]
        int k;
        for (k = n-2; k >= 0; --k)
            if (nums[k] < nums[k+1]) break;
        
        // already last one (descending order), return ascending order
        if(k == -1) { reverse(nums, 0, n-1); return; }
        
        //find largest l > k such that nums[l] > nums[k]
        int l;
        for (l = n-1; l > k; --l)
            if (nums[l] > nums[k]) break;
        //swap nums[l] and nums[k]
        swap(nums, k, l);
        //reverse elements after k
        reverse(nums, k+1, n-1);
    }
    
    //reserve array elements nums[lo .. hi]
    void reverse(vector<int>& nums, int lo, int hi) {
        for (int i = 0; i < (hi-lo+1)/2; ++i) 
            swap(nums, lo+i, hi-i);        
    }
    
    //swap two array elements
    void swap(vector<int>& nums, int i, int j) {
        int t = nums[i]; nums[i] = nums[j]; nums[j] = t;
    }
};
