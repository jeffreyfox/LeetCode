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
// Trick: in if condition, first check breakable, then check wordDict.count() will cause program to run slightly faster, because array look-up is faster than hash table lookup.

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<string> result;
        if(s.empty() || wordDict.empty()) return result;
        int n = s.size();
        vector<bool> breakable(n+1, false); //whether s[i, n) is breakable?
        breakable[n] = true; //empty string breakable
        for(int i = n-1; i >= 0; --i) {
            for(int len = 1; len <= n-i; ++len) {
                if(breakable[i+len] && wordDict.count(s.substr(i, len))) {
                    breakable[i] = true;
                    break;
                }
            }
        }
	//if string s not breakable, just return (avoid TLE)
        if(!breakable[0]) return result;
        
        string tmp;
        dfs(s, 0, breakable, wordDict, tmp, result);
        return result;
    }
    //check s[k .. end)
    void dfs(string& s, int k, vector<bool>& breakable, unordered_set<string>& wordDict, string tmp, vector<string>& result) {
        int n = s.size();
        if(k == n) {
            result.push_back(tmp);
            return;
        }
        //s's length i substring starting at k
        for(int i = 1; k+i <= n; ++i) {
            string sub = s.substr(k, i);
            if(breakable[k+i] && wordDict.count(sub)) {
                if(tmp == "") dfs(s, k+i, breakable, wordDict, sub, result);
                else dfs(s, k+i, breakable, wordDict, tmp + " " + sub, result);
            }
        }
    }
/*
    // An alternative dfs function passing reference of partial solution tmp. Remember its end position, append new strings, and erase them 
    // using C++'s erase() function.
    void dfs(string& s, int k, vector<bool>& breakable, unordered_set<string>& wordDict, string& tmp, vector<string>& result) {
        int n = s.size();
        if(k == n) {
            result.push_back(tmp);
            return;
        }
        //s's length i substring starting at k
        int j = tmp.size(); //remember tmp's end position
        for(int i = 1; k+i <= n; ++i) {
            string sub = s.substr(k, i);
            if(breakable[k+i] && wordDict.count(sub)) {
                if(tmp == "") tmp = sub;
                else tmp += " " + sub;
                dfs(s, k+i, breakable, wordDict, tmp, result);
                tmp.erase(j); //revert back to original
            }
        }
    }
*/
};
	
// Solution 2. Dynamic programming, but store all the possible breaking points of each substring s[i, n). Checking each substring is breakable simply reduces to checking whether the array for possible breaking points is empty. For string s[i, n), check if s[i, j) is in dictionary and s[j, n) is breakable by dynamic programming.

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<string> result;
        if(s.empty() || wordDict.empty()) return result;
        int n = s.size();
        vector<vector<int> > breakpos(n+1); //breaking position of s[i, n)
        for(int i = n-1; i >= 0; --i) {
            for(int len = 1; len <= n-i; ++len) {
                if((len == n-i || !breakpos[i+len].empty()) && wordDict.count(s.substr(i, len))) {
                    breakpos[i].push_back(i+len);
                }
            }
        }
        if(breakpos[0].empty()) return result;
        
        string tmp;
        dfs(s, 0, breakpos, tmp, result);
        return result;
    }
    //check s[k .. end)
    void dfs(string& s, int k, vector<vector<int>>& breakpos, string tmp, vector<string>& result) {
        int n = s.size();
        if(k == n) {
            result.push_back(tmp);
            return;
        }
        //s's length i substring starting at k
        for(int j = 0; j < breakpos[k].size(); ++j) {
            int pos = breakpos[k][j];
            if(tmp == "") dfs(s, pos, breakpos, s.substr(k, pos-k), result);
            else dfs(s, pos, breakpos, tmp + " " + s.substr(k, pos-k), result);
        }
    }
};

// Solution 3. Recursive solution with top-down memoization DP. Fastest (4ms) solution.
// Store the possible break solutions for a string in a map (memoization). First search result in map, if not there, do real business.
// To avoid TLE, first check if the word s is breakable or not by examining all its substrings starting at i (ends at s.end()) and see if any belongs to dictionary. If none is in dictionary, then there's no solution.
// If there is solution, then we systematically break the string into 2 parts,with the first part length varying from 1 to n-1. Each time if first part is in dictionary, recursively call wordBreak for second part, and construct the solution for s from the solution of second part.
// Finally, before return, do not forget to write the result to dp table.

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        //first search in memoization table
        if(dp.count(s)) return dp[s];
        
        vector<string> result;
        int i = 0, n = s.size();
        for(i = 0; i < n; ++i) { //check if s[i, n) is in dict
            if(wordDict.count(s.substr(i))) break;
        }
        if(i == n) return result; //no solution
        
        //now search substrings
        if(wordDict.count(s)) result.push_back(s); //whole string is solution
        for(int len = 1; len < n; ++len) {
            string str = s.substr(0, len);
            if(wordDict.count(str)) {
                vector<string> tmp = wordBreak(s.substr(len), wordDict);
                for(auto it : tmp) {
                    result.push_back(str + " " + it);
                }
            }
        }
        dp[s] = result;
        return result;
    }
    unordered_map<string, vector<string> > dp; //memoization
};

