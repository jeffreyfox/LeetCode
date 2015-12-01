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

The relation can be expressed as:
maxProf[j][k] = max(maxProf[j-1][k], price[j] + tmpMax[j][k-1])

To avoid calculating the max for all jj's, we can keep a storage called tmpMax for the quantity max(maxProf[jj][k-1] - price[jj]) as j is incremented:
- j = 0, tmpMax[j][k] = -price[0];  // maxProf[0][k] = 0
- k = 0, tmpMax[j][k] = max(tmpMax[j-1][k], -price[j])  // maxPro[0][-1] = 0
- j > 0 & k > 0, tmpMax[j][k] = max(tmpMax[j-1][k], maxProf[j][k-1]-price[j])

so, for each new j, do this:
for(int kk = 1; kk < k; ++kk)  {
    mp[j][k] = max(mp[j-1][k], price[j] + tmp[jj][k-1]);
    tmp[j][k] = max(tmp[j-1][k], mp[
}
where tmp[jj][k] is the maximum of mp[jj][k-1]-price[jj] observed so far (for all jj < j)
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
        //now the real business
        vector<vector<int> > maxProf(n, vector<int>(k+1, 0)); //maxProfit performing upto k transactions
        vector<vector<int> > tmpMax(n, vector<int>(k+1, 0)); //max of (maxProf[jj][k-1] - price[jj]) for all jj <= j.
        for(int j = 0; j < n; ++j) {
            for(int kk = 1; kk < k; ++kk) {
                maxProf[j][kk] = max(maxProf[j][kk], prices[j] + tmpMax[j][kk-1]);
                if(j == 0) tmpMax[j][kk] = maxProf[0][kk-1] - prices[0];
                else tmpMax[j][kk] = max(tmpMax[j-1][kk], maxProf[j][kk-1]-prices[j]);
            }
        }
        return maxProf[n-1][k];
    }
};

/// Space optimized DP solution, also time-optimized for k > n/2 case.

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
		int n = prices.size();
		if(n <= 1) return 0;
		int maxAll = 0; //maximum of all posibilities
		
		//notice the simple case where k exceed half of n! This reduces to buy_and_sell_stock_II!
		//because, the maximum number of non-continuous POSITIVE segments in array of size N is (N+1)/2. e.g N = 5, PNPNP, N = 6, PNPNPN.
		//check the price difference array which is of size n-1, thus maximum number of non-cont. POSITIVE segment is n/2.
		if (k > n/2) {
		    for (int i = 1; i < n; ++i)  {
		        int diff = prices[i] - prices[i-1];
		        if (diff > 0) maxAll += diff;
		    }
		    return maxAll;
		}
		
		int numTrans = k; //number of transactions
		//mp[j] is maximum prof at the end of day j after performing at most k transactions
		vector<int> mp(n, 0); 
		
		//maxProf[k][j] is the maximum of two cases:
		// a. no selling at day j, so upto k transactions (including 1,2,...k) at end of day j-1: mp[k][j-1]
		// b. selling at day j: for some jj < j, perform upto k-1 transactions at jj, and buy at jj and sell at day j,
		// the profit is the maximum of mp[k-1][jj] + prices[j] - prices[jj] among all 0 <= jj < j. Thus:
		// mp[k][j] = max( mp[k][j-1], prices[j] + max(mp[k-1][jj]-prices[jj], for all jj < j) )
		// when we increase j, we keep a variable tmpMax storing the last term and update properly.
		// The clever part is to take prices[j] out of the maximum expression of jj.
		
		for(int k = 1; k <= numTrans; ++k) {
			int tmpMax = mp[0] - prices[0]; //k = 1, tmpMax = mp[k-1][0] - prices[0];
			for(int j = 1; j < n; ++j) {
			    int old = mp[j]; //mp[k-1][j]
				mp[j] = max(mp[j-1], tmpMax+prices[j]);
				tmpMax = max(tmpMax, old-prices[j]);
				maxAll = max(maxAll, mp[j]);
			}
		}
		return maxAll;
    }
};
