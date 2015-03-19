class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        sort(S.begin(), S.end());
        vector<int> ss;
        vector<vector<int> > ret;
        dfs(0, S, ss, ret);
        return ret;
    }
    //construct solution using elements S[i .. n-1], i = 0, n-1
    void dfs(int i, vector<int> &S, vector<int> &ss, vector<vector<int> > &ret) {
        if(i == S.size()) {
            ret.push_back(ss);
            return;
        }
        //not include S[i]
        dfs(i+1, S, ss, ret);
        //incldue S[i]
        ss.push_back(S[i]);
        dfs(i+1, S, ss, ret);
        ss.erase(ss.end()-1);//backtrack
    }
};
