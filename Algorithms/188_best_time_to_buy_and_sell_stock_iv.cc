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
