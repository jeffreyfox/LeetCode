// Use next permutation algorithm to print permutations in lexigraphical order.
// Also works for when duplicated entries exist
// Use a counter to print exactly n! permutations

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > ret;
        ret.push_back(nums);
        int count = factorial(nums.size());
        for (int i = 1; i < count; ++i) {
            nextPermutation(nums);
            ret.push_back(nums);
        }
        return ret;
    }
    
    int factorial(unsigned int n) {
        return (n == 1) ? 1 : n * factorial(n-1);
    }
    // next permutation routine from problem #31
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
