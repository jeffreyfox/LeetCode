/// Allow infinte transitions. Very simple. Just add up all positive differences!

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max_profit = 0;
        for (int i = 1; i < prices.size(); ++i) {
            int diff = prices[i] - prices[i-1];
            if (diff > 0) max_profit += diff;
        }
        return max_profit;
    }
};
