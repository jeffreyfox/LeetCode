/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

/*
What is a transaction? Buy followed by sell. K transactions means a sequence of buy - sell - buy - sell - ... - buy - sell, where no two transations occur on the same date. If a sell and a buy fall on the same date, we can just merge them into one transaction.
So the key is to find non-overlapping intervals each of which has start and end corresponding to buy and sell dates.
Why non-overlapping? Because the problem requires sell before buy a new stock.
Profit is incurred only after selling a pre-purchased stock (e.g. at the end of opening interval)

Here is how to solve it with dynamic programming:
Let the max profit after day j, when performing up to kk transactions be maxProf[j][k]. It can be the maximum of the two scenarios:
1. No selling at day j, so we inherit the max profit after day j-1, maxProf[j-1][k]:
2. max profit after day jj when performing up to k-1 transactions, then buy stock at day jj, and sell at day j. The prior transactions can end at day jj, because in that case we can merge the sell/buy at jj, and instead sell at j, which in total is up to k-1 transactions, and thus also falls into the up to k transactions category. You can also make jj equal to j, and that is simply maxProf[j-1][k] (no transaction on day j). In this case, the max profit will be:
   max( maxProf[jj][k-1] + price[j] - price[jj] ) for all 0 <= jj <= j
 = price[j] + max (maxProf[jj][k-1] - price[jj]) for all 0 <= jj <= j

To avoid calculating the max for all jj's, we can keep a storage called tmpMax for the quantity max(maxProf[jj][k-1] - price[jj]) as j is incremented. So the DP relation can be expressed as:

maxProf[j][k] = max(maxProf[j-1][k], price[j] + tmpMax[j][k-1]),    j > 0 and k > 0
              = 0,   j = 0 or k = 0

tmpMax[j][k] = max(tmpMax[j-1][k], maxProf[j][k-1]-price[j]),  j > 0 and k > 0
             = max(tmpMax[j-1][k], -price[j]),    j > 0 and k = 0   // maxPro[0][-1] = 0
             = -price[0],   j = 0   // maxProf[0][k] = 0

We noticed that maxProf[0][k] and maxProf[j][0] are always zero, and tmpMax[0][k] = -price[0] for all k, so we can initialize the array and later do not iterate over j = 0 and k = 0.
*/

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int result = 0;
        if(k >= n/2) {
            for(int i = 1; i < n; ++i) {
                result += max(0, prices[i] - prices[i-1]);
            }
            return result;
        }
        vector<vector<int> > maxProf(n, vector<int>(k+1, 0)); //maxProfit performing upto k transactions
        vector<vector<int> > tmpMax(n, vector<int>(k+1, 0)); //max of (maxProf[jj][k] - price[jj]) for all 0 <= jj <= j.

        for(int kk = 0; kk < k; ++kk) tmpMax[0][kk] = -prices[0];

        for(int j = 1; j < n; ++j) {
            tmpMax[j][0] = max(tmpMax[j-1][0], -prices[j]); //handle kk = 0 case
            for(int kk = 1; kk <= k; ++kk) {
                maxProf[j][kk] = max(maxProf[j-1][kk], prices[j] + tmpMax[j][kk-1]);
                tmpMax[j][kk] = max(tmpMax[j-1][kk], maxProf[j][kk]-prices[j]);
            }
        }
        return maxProf[n-1][k];
    }
};

/*
Space optimized solution: we noticed that maxProf[j][k] only requires values at j-1 and k-1, so we can replace the 2D array with 1D, by reducing the dimension for the day. We use the same array to track the maxProfit for kk transactions for the current day, and update it for the next day.
*/

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int result = 0;
        if(k >= n/2) {
            for(int i = 1; i < n; ++i) {
                result += max(0, prices[i] - prices[i-1]);
            }
            return result;
        }
        vector<int> maxProf(k+1, 0); //maxProfit performing upto k transactions
        vector<int> tmpMax(k+1, -prices[0]); //max of (maxProf[jj][k] - price[jj]) for all 0 <= jj <= j.

        for(int j = 1; j < n; ++j) {
            tmpMax[0] = max(tmpMax[0], -prices[j]); //handle kk = 0 case
            for(int kk = 1; kk <= k; ++kk) {
                maxProf[kk] = max(maxProf[kk], prices[j] + tmpMax[kk-1]);
                tmpMax[kk] = max(tmpMax[kk], maxProf[kk]-prices[j]);
            }
        }
        return maxProf[k];
    }
}
