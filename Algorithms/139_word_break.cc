/*
 Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code". 
*/

/// Dynamic programming, store whether s's length-i substring can be broken into an array.
/// When found, just break;

class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        if(s.empty()) return true;
        int n = s.size();
        vector<bool> breakable(n+1, false); //whether s's length-i subtring can be broken
        breakable[0] = true;
        for(int i = 1; i <= n; ++i) { //check length i ending at s[i-1]
            for(int j = 0; j < i; ++j) { //check s[0 .. j-1] and s[j .. i-1]
                if(breakable[j] && wordDict.count(s.substr(j, i-j))) { breakable[i] = true; break; }
            }
        }
        return breakable[n];        
    }
};
