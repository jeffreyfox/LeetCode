/*
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

Example:

Given [3, 1, 5, 8]

Return 167

    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

Credits:
Special thanks to @dietpepsi for adding this problem and creating all test cases.
*/

/*
Standard dynamic programming. Use dp[i][j] to store the maximum coins for popping balloons [i .. j]. There are l = j-i+1 possibilities, each corresponds to popping k-th balloon at last ( i <= k <= j). The points obtained in this scenario is:

  i-1 i ... k-1 k k+1 ... j j+1
We keep k until the last step, so the coins we get will be the coins won from breaking [i .. k-1], and [k+1 .. j], and in the end, we are left with [i-1, k, j+1], so the last step we get nums[i-1]*nums[k]*nums[j+1].

To avoid array bounds checking, we insert 1 to front and end of the nums array.

We also need to have n+2 dimension for the dp vector.
*/

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.push_back(1);
        nums.insert(nums.begin(), 1);
        //dp[i][j]:  the maximum coins for nums[i .. j], 1 <= i <= j <= n
        vector<vector<int> > dp(n+2, vector<int>(n+2, 0));
        for(int len = 1; len <= n; ++len) {
            for(int i = 1; i + len <= n+1; ++i) {
                int j = i+len-1;
                //now check max for nums[i .. j], try all cases where k breaks last (i <= k <= j)
                for(int k = i; k <= j; ++k) {
                    dp[i][j] = max(dp[i][j], dp[i][k-1] + dp[k+1][j] + nums[i-1]*nums[k]*nums[j+1]);
                }
            }
        }
        return dp[1][n];
    }
};

