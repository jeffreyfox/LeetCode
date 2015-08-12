/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

  [
    ["aa","b"],
    ["a","a","b"]
  ]
*/

/// use DFS. Don't need to use dynamic programming, since there is no overlapping subproblems. Only checked ispalindrome(s, i, j) once for each i, j pair.

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<string> tmp;
        vector<vector<string> > ret;
        if(s.empty()) return ret;
        
        dfs(s, 0, tmp, ret);
        return ret;
    }
    
    void dfs(const string& s, int i, vector<string>& tmp, vector<vector<string> >& ret) {
        if(i == s.size()) {
            ret.push_back(tmp);
            return;
        }
        tmp.push_back(""); //add one entry
        for (int j = i; j < s.size(); ++j) {
            if(isPalindrome(s, i, j)) {
                tmp.back() = s.substr(i, j-i+1);
                dfs(s, j+1, tmp, ret);
            }
        }
        tmp.resize(tmp.size()-1); //remove last entry
    }
    bool isPalindrome(const string& s, int i, int j) {
        int len = j-i+1;
        for(int k = 0; k < len/2; ++k) {
            if(s[i+k] != s[j-k]) return false;
        }
        return true;
    }
};
