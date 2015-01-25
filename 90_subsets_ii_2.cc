class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
       //first sort (bubble sort)
	   for(unsigned int i = 0; i < S.size(); ++i) {
		   for(unsigned int j = S.size() - 1; j >= i+1; --j) {
				if(S[j] < S[j-1]) {
					int temp = S[j];
					S[j] = S[j-1];
					S[j-1] = temp;
				}
		   }
	   }
	
		//algorithm: all subset of S1 ... S(n-1) and n Sn consists of
		// (a) all subset of S1 ... S(n-1), including []
		// (b) each subset of S1 ... S(n-1) appended by Sn, [Sn, Sn], ... [n Sn's]
		unsigned int n = S.size();
		vector<vector<int> > ret;
		ret.push_back(vector<int>()); //push-back empty set
		
		for(unsigned int k = 0; k < n; ) {
			int j = k; // last entry of existing subsets
			while(j < n && S[j] == S[k]) j++; //j points to first entry not equal to k
			//should insert S[k] from 1 to j-k into existing subsets
			int old_size = ret.size();
			for(int i = 0; i < old_size; ++i) { //loop over existing subsets
				vector<int> new_entry = ret[i];
				for(int cnt = 1; cnt <= j-k; ++cnt) {
					new_entry.push_back(S[k]);
					ret.push_back(new_entry);
				}
			} //end of i
			k = j; //reset k!
		} //end of k
		return ret;
    }
};
