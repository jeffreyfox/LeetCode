/// Dynamic programmming solution that extends to general k cases.
class Solution {
public:
    int maxProfit(vector<int> &prices) {
		int n = prices.size();
		if(n <= 1) return 0;
		int numTrans = 2; //number of transactions
		//mp[k][j] is maximum prof at the end of day j after performing at most k transactions
		vector<vector<int> > mp(numTrans+1, vector<int>(n, 0)); 
		int maxAll = 0; //maximum of all posibilities
		//maxProf[k][j] is the maximum of two cases:
		// a. no selling at day j, so upto k transactions (including 1,2,...k) at end of day j-1: mp[k][j-1]
		// b. selling at day j: for some jj < j, perform upto k-1 transactions at jj, and buy at jj and sell at day j,
		// the profit is the maximum of mp[k-1][jj] + prices[j] - prices[jj] among all 0 <= jj < j. Thus:
		// mp[k][j] = max( mp[k][j-1], prices[j] + max(mp[k-1][jj]-prices[jj], for all jj < j) )
		// when we increase j, we keep a variable tmpMax storing the last term and update properly.
		// The clever part is to take prices[j] out of the maximum expression of jj.
		for(int k = 1; k <= numTrans; ++k) {
			int tmpMax = mp[k-1][0] - prices[0]; //k = 1, tmpMax = mp[k-1][0] - prices[0];
			for(int j = 1; j < n; ++j) {
				mp[k][j] = max(mp[k][j-1], tmpMax+prices[j]);
				tmpMax = max(tmpMax, mp[k-1][j]-prices[j]);
				maxAll = max(maxAll, mp[k][j]);
			}
		}
		return maxAll;
    }
};
