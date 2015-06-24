// perform swaps iteratively, back-tracking
// Note that this method does not print the permutations in lexigraphical order!
// The algorithm to print the lexigraphical order is in 046_permutaionts_2.cc.

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > ret;
        permute(nums, 0, ret);
        return ret;
    }
    //permute nums[k .. end)
    void permute(vector<int>& nums, int k, vector<vector<int> >& ret) {
        int n = nums.size();
        if(k == n-1) ret.push_back(nums);
        for(int i = k; i < n; ++i) {
            swap(nums[k], nums[i]);
            permute(nums, k+1, ret);
            swap(nums[k], nums[i]);
        }
    }
    void swap(int &a, int &b) {
        int t = a; a = b; b = t;
    }
};
