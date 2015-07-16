// Use next permutation algorithm to print permutations in lexigraphical order.
// use a tag to indicate the status of permutation. If reaching the last permutation (descending order), return false. 
// Also works for cases when duplicated entries exist
// Attention: If use a counter to print exactly n! permutations, then does not for cases where duplicated entries exist!

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > ret;
        //first sort the initial array!
        sort(nums.begin(), nums.end()); 
        while(1) {
            ret.push_back(nums);
            if(!nextPermutation(nums)) break; //reaching the end
        }
        return ret;
    }
    
    // slightly modified next permutation routine from problem #31
    bool nextPermutation(vector<int>& nums) {
        int n = nums.size();
        //find largest k such that nums[k] < nums[k+1]
        int k;
        for (k = n-2; k >= 0; --k)
            if (nums[k] < nums[k+1]) break;
        
        // already last one (descending order), return false
        if(k == -1) return false;
        
        //find largest l > k such that nums[l] > nums[k]
        int l;
        for (l = n-1; l > k; --l)
            if (nums[l] > nums[k]) break;
        //swap nums[l] and nums[k]
        swap(nums, k, l);
        //reverse elements after k
        reverse(nums, k+1, n-1);
        return true;
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
