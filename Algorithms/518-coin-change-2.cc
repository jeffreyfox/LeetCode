/*
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.

You may assume that you have an infinite number of each kind of coin.

The answer is guaranteed to fit into a signed 32-bit integer.

 

Example 1:

Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
Example 2:

Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.
Example 3:

Input: amount = 10, coins = [10]
Output: 1
 

Constraints:

1 <= coins.length <= 300
1 <= coins[i] <= 5000
All the values of coins are unique.
0 <= amount <= 5000
*/

// This solution results in RTE.
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        sort(coins.begin(), coins.end(), std::greater<int>());
        int n = coins.size();
        // mem[i][amount]: counts of forming amount from coins[i .. n)        
        vector<vector<int>> mem(n, vector<int>(amount+1, 0));
        return helper(amount, coins, 0, mem);        
    }
    
    // start picking from coins[i .. end)
    int helper(int amount, vector<int> &coins, int i, vector<vector<int>> &mem) {
        if (amount == 0) return 1;
        if (amount < 0 || i == coins.size()) return 0;
        if (mem[i][amount] > 0) return mem[i][amount];        
        // pick coins[i] 0, 1 .. etc times
        int count = 0;
        for (int k = 0; k <= amount / coins[i]; ++k) {
            count += helper(amount - k * coins[i], coins, i+1, mem);
        }
        mem[i][amount] = count;
        return count;
    }
};
