/*
You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.
*/

// Dynamic programmming (top-down) with memoization

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(amount <= 0) return 0;
        dp.resize(amount+1, 0);
        sort(coins.begin(), coins.end());
        return getFewestNum(coins, amount);
    }
    //greedy
    int getFewestNum(vector<int>& coins, int amount) {
        if(dp[amount] != 0) return dp[amount];
        int min_val = INT_MAX;
        for(int i = 0; i < coins.size(); i++) {
            if(amount < coins[i]) break;
            else if(amount == coins[i]) { min_val = 1; break; }
            else {
                int tmp = getFewestNum(coins, amount - coins[i]);
                if(tmp != -1 && min_val > tmp+1) min_val = tmp+1;
            }
        }
        if(min_val == INT_MAX) min_val = -1;
        dp[amount] = min_val;
        return min_val;
    }
    vector<int> dp;
};
