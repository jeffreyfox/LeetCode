/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
*/

/// Greedy one pass O(n) solution:

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int max_so_far = 0, max_all = 0;
        for(int i = 1; i < n; ++i) {
            int change = prices[i] - prices[i-1];
            if(max_so_far <= 0) max_so_far = change;
            else max_so_far += change;
            max_so_far = max(0, max_so_far);
            max_all = max(max_so_far, max_all);
        }
        return max_all;
    }
};

// Keeps track of the lowest price we see so far and see how much profit we can get by selling at the current price.

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty() || prices.size() == 1) return 0;
        int min = prices[0];
        int n = prices.size();
        int result = 0;
        for (int i = 1; i < n; ++i) {
            if (prices[i] < min) {
                min = prices[i];
            } else {
                result = max(result, prices[i] - min);
            }
        }
        return result;
    }
};
