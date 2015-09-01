/*
Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"]. 
*/

//DP solution: use an array to store whether substring s[i .. end) is breakable.
//Then do a DFS, when checking the conditions, first check if breakable (guaranteed O(1)), and then whether the substring s[i, i+len) is in dictionary (amortize O(1)). 

// Avoid TLE, if string is not breakable at all, return.

class Solution {

public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        int n = s.size();
        vector<string> ret;
        string partial;
        //whether s[i, n-1] is breakable, i = [0, n]
        vector<bool> breakable(n+1, false);
        breakable[n] = true; //empty string is forced to be breakable
        for (int i = n-1; i >= 0; i--) {
            for (int j = i+1; j <= n; j++) {
                if(breakable[j] && wordDict.count(s.substr(i, j-i))) { breakable[i] = true; break; }
            }
        }
        //if string s not breakable, just return (avoid TLE error)
        if(!breakable[0]) return ret;
        dfs(s, 0, wordDict, breakable, partial, ret);
        return ret;
    }
    void dfs(const string& s, int i, unordered_set<string>& wordDict, vector<bool>& breakable, string& partial, vector<string>& ret) {
        int n = s.size();
        if(i == n) {
            ret.push_back(partial);
            return;
        }
        int ipos = partial.size();
        for(int len = 1; i + len <= n; ++len) {
            if(breakable[i+len] && wordDict.count(s.substr(i, len))) {
                 if(!partial.empty()) partial += " ";
                 partial += s.substr(i, len);
                 dfs(s, i+len, wordDict, breakable, partial, ret);
                 partial.erase(ipos); //revert
            }
        }
    }
};
