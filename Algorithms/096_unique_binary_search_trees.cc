class Solution {
public:
    int numTrees(int n) {
        if(n == 0 || n == 1) return 1;
        vector<int> nums(n+1, 0);
        nums[0] = nums[1] = 1;
        for(int k = 2; k <= n; ++k) {
            for(int r = 1; r <= k; ++r) {
                nums[k] += nums[r-1]*nums[k-r];
            }
        }
        
        return nums[n];
    }
};
