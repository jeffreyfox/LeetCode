/*
Note: This is an extension of House Robber.

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/

// One pass DP solution. Use two variables, one meaning maximum including first house, second meaning maximum excluding first house.
// Special treatment for the last house.

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        //dp1: maximum including first house, dp2: maximum excluding first house
        vector<int> dp1(n, 0), dp2(n, 0);
        dp1[0] = nums[0]; dp1[1] = nums[0];
        dp2[0] = 0; dp2[1] = nums[1];
        for (int i = 2; i < n-1; ++i) {
            dp1[i] = max(dp1[i-2] + nums[i], dp1[i-1]); 
            dp2[i] = max(dp2[i-2] + nums[i], dp2[i-1]); 
        }
        //last one
        dp1[n-1] = dp1[n-2];
        dp2[n-1] = max(dp2[n-3] + nums[n-1], dp2[n-2]); 
        return max(dp1[n-1], dp2[n-1]);
    }
};

/// Two pass DP solution. Each pass calls original rob, once excluding nums[0] and once excluding nums[n-1]. Compare the two and return the maximum
/// robLin is the original rob function on a linear street.

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        return max(robLin(nums.begin(), nums.end()-1), robLin(nums.begin()+1, nums.end()));
    }
    int robLin(vector<int>::const_iterator beg, vector<int>::const_iterator end) {
        int n = end - beg;
        if(n == 0) return 0;
        if(n == 1) return *beg;
        if(n == 2) return max(*beg, *(beg+1));
        int last = max(*beg, *(beg+1));
        int lastlast = *beg;
        int curr = 0;
        for(vector<int>::const_iterator it = beg+2; it != end; it++) {
            curr = max(lastlast + *it, last);
            lastlast = last;
            last = curr;
        }
        return curr;
    }
};

