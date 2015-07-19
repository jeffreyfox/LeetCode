/// Greedy one pass O(n) solution:

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max_so_far = 0;
        int max_all = 0;
        for (int i = 1; i < prices.size(); ++i) {
            max_so_far += (prices[i]-prices[i-1]);
            if (max_so_far < 0) max_so_far = 0;
            else max_all = max(max_all, max_so_far);
        }
        return max_all;
    }
};
