/*
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

 

Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
Example 2:

Input: coins = [2], amount = 3
Output: -1
Example 3:

Input: coins = [1], amount = 0
Output: 0
 

Constraints:

1 <= coins.length <= 12
1 <= coins[i] <= 231 - 1
0 <= amount <= 104
*/

// Solution using top-down DP with memoization.
// Uses a 1D mem table to store answers already explored. 0 means not explored, -1 means can't make amount from coins.
// When amount is 0, return 0 directly instead of looking up the mem table.
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // 0 means uninitialized. -1 means can't make amount from coins.
        vector<int> mem(amount+1, 0);
        return getCount(coins, amount, mem);
    }
    int getCount(vector<int>& coins, int amount, vector<int> &mem) {
        if (amount < 0) return -1;
        if (amount == 0) return 0;
        if (mem[amount] != 0) return mem[amount];
        int min_value = INT_MAX;
        for (int coin : coins) {
            if (coin > amount) continue;
            int value = getCount(coins, amount - coin, mem) + 1;
            if (value != 0 && value < min_value) min_value = value;
        }
        mem[amount] = (min_value == INT_MAX) ? -1 : min_value;
        return mem[amount];
    }
};
