// Recursive solution. Need to use a table to store the numbers used in current k-th position. We can't use something simpler such as checking current to be exchanged ia equal to previously exchanged one, because the subarray maybe unsorted, for example, given aabbccd, and after a while we have bcd|caba, and the second part is unsorted. Unless using a set structure, there is no way of preventing c to be swapped with second a, because the previous is a 'b'.

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int>& nums) {
        vector<vector<int> > ret;
        sort(nums.begin(), nums.end());
        permute(nums, 0, ret);
        return ret;
    }
    
    //permute nums[k .. end)
    void permute(vector<int>& nums, int k, vector<vector<int> >& ret) {
        int n = nums.size();
        if(k == n-1) { ret.push_back(nums); return; }
        set<int> used;
        for(int i = k; i < n; ++i) {
            if (used.find(nums[i]) != used.end()) continue; //ignore duplicated exchange
            used.insert(nums[i]);
            swap(nums[k], nums[i]);
            permute(nums, k+1, ret);
            swap(nums[k], nums[i]);
        }
    }
    void swap(int &a, int &b) {
        int t = a; a = b; b = t;
    }
};
