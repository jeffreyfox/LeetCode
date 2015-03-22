class Solution {
public:
	vector<vector<int> > subsets(vector<int> &S) {
		vector<vector<int> > ret;
		vector<int> path;
		sort(S.begin(), S.end());
		iterative(S, 0, path, ret);
		return ret;
	}
	//get letter for digit[i]
	void iterative(const vector<int>& S, int beg, 
	               const vector<int>& path, vector<vector<int> >& ret) {
		if(beg == S.size())	ret.push_back(path);		   
		else {
			ret.push_back(path);
			for(int k = beg; k < S.size(); ++k) { //choose among possible candidates
				vector<int> newpath(path);
				newpath.push_back(S[k]);
				iterative(S, k+1, newpath, ret);
			}
		}
	}
};
