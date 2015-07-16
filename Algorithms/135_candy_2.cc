// Smart solution, two passes

class Solution {
public:
	int candy(vector<int> &ratings) {
		int n = ratings.size();
		if(n == 0) return 0;
		if(n == 1) return 1;
		vector<int> candies(n, 1); //initially every one has one candy
		int total = n;
		for(int k = 1; k < n; ++k) {
			if(ratings[k] > ratings[k-1] && candies[k] <= candies[k-1]) {
			    total -= candies[k];
				candies[k] = candies[k-1] + 1;
				total += candies[k];
			}
		}
		for(int k = n-2; k >= 0; --k) {
			if(ratings[k] > ratings[k+1] && candies[k] <= candies[k+1]) {
			    total -= candies[k];
				candies[k] = candies[k+1] + 1;
				total += candies[k];
			}
		}
		return total;
	}
};
