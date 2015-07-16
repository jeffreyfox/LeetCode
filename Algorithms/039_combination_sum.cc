// Iterative solution of combination sum
class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
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
			for(int k = beg; k < candidates.size(); ++k) {
				vector<int> newpath(path);
				newpath.push_back(candidates[k]); //pick k
				iterative(candidates, target-candidates[k], k, newpath, ret);
			}
		}
	}
};
