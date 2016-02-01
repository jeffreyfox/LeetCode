/*
 Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code". 
*/

/// Dynamic programming, store whether s's length-i substring can be broken into an array. 
/// When found, just break;
/// Optimization: for j goes opposite direction to i, so that we encountered lastly found breakable item first.
/// 4ms.

class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        //if(s.empty()) return true;
        int n = s.size();
        vector<bool> breakable(n+1, false); //whether s[i, n) is breakable
        breakable[n] = true; //s[n, n) is defined to be true
        for(int i = n-1; i >= 0; --i) { //check s[i, n)
            for(int j = i+1; j <= n; ++j) { //check s[i, j) and s[j, n), j direction optimized so that we encountered lastly set breakable[j] first
                if(breakable[j] && wordDict.count(s.substr(i, j-i))) { 
                    breakable[i] = true; 
                    break; 
                }
            }
        }
        return breakable[0];        
    }
};

// Solution 2. Same solution as 1 except starting from beginning
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1,false);
        dp[0]=true;
        for(int i=1; i<=n; i++)  {
            for(int j = i-1; j >= 0; j--) {
                if(dp[j] && wordDict.count(s.substr(j,i-j))) {
                    dp[i]=true;
                    break; //next i
                }
            }
        }
        return dp[n];
    }
};

// Solution 3. DP with memoization (16ms)
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        if(breakable.count(s)) return breakable[s];
        if(wordDict.count(s)) {
            breakable[s] = true; //memoization
            return true;
        }
        int n = s.size();
        for(int i = 1; i < n; ++i) {
            if(wordDict.count(s.substr(0, i)) && wordBreak(s.substr(i), wordDict)) {
                breakable[s] = true;
                return true;
            }
        }
        breakable[s] = false;
        return false;
    }
    unordered_map<string, bool> breakable;
};

