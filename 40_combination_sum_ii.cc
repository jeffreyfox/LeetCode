class Solution {
public:
	vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
		vector<vector<int> > ret;
		vector<int> path;
		sort(candidates.begin(), candidates.end());
		iterative(candidates, target, 0, path, ret);
		return ret;
	}
	void iterative(vector<int> &candidates, int target, int beg,
	               vector<int> &path, vector<vector<int> > &ret) {
		if(target == 0) {
			ret.push_back(path);
		}
		else if (target > 0) {
			int pre = INT_MIN;
			for(int k = beg; k < candidates.size(); ++k) {
				int cur = candidates[k];
				if(cur == pre) continue;
				vector<int> newpath(path);
				newpath.push_back(cur); //pick k
				iterative(candidates, target-cur, k+1, newpath, ret);
				pre = cur;
			}
		}
	}
};
