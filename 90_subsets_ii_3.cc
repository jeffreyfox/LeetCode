class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        sort(S.begin(), S.end());
        map<int, int> count;
        for(int k = 0; k < S.size(); ++k) count[S[k]] ++;
        
        vector<int> ss;
        vector<vector<int> > ret;
        dfs(0, S, count, ss, ret);
        return ret;
    }
    
    //construct solution using elements S[i .. n-1], i = 0, n-1
    void dfs(int i, vector<int> &S, map<int, int> &count, vector<int> &ss, vector<vector<int> > &ret) {
        if(i == S.size()) {
            ret.push_back(ss);
            return;
        }
        int ct = count[S[i]];
        //incldue 0 to max-num of S[i] 
        for(int j = 0; j <= ct; ++j) {
            for(int k = 1; k <= j; ++k) ss.push_back(S[i]);
            dfs(i+ct, S, count, ss, ret);
            for(int k = 1; k <= j; ++k) ss.erase(ss.end()-1);
        }
    }
};
