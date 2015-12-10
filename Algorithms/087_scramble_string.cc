/*
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t

To scramble the string, we may choose any non-leaf node and swap its two children.
For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t

We say that "rgeat" is a scrambled string of "great".
Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a

We say that "rgtae" is a scrambled string of "great".
Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1. 
*/

/*
Solution 1. Recursive dfs with branching by anagram checking, 8ms. 

If no branching, time complexity is around 5^n (exponential algorithm!)
f(n) = 2*(f(1)+f(n-1)) + 2*(f(2)+f(n-2)+ ... + 2(f(n-1)+f(1)).
f(n+1) = ...
f(n+1) = 5f(n) => f(n) = 5^n.

Try all ways of cutting the string into two parts, and recursively check if the two parts are scramble strings. Check every possibilities of partition:
e.g.  a0-a4 v.s. b0-b4
check  a0 | a1-a4 v.s. b0 | b1-b4; 
       a0a1 | a2-a4 v.s. b0b1 | b2-b4 ... 
and
       a0 | a1-a4 v.s. b0-b3 | b4; 
       a0a1 | a2-a4 v.s. b0-b2 | b3b4 ...

Anagram checking: indexed map from 0 to 256. If we assume only a-z characters and use 26 entries, we can reduce the time to 4ms.

search s1, increment character counts,
search s2, decrement character counts. If found a negative value, then we know that they are not anagram.
*/

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.size() != s2.size()) return false;
        if(s1.empty()) return true; //empty string
        return isScramble(s1, 0, s2, 0, s1.size());
    }

    bool isScramble(const string& s1, int lo1, const string& s2, int lo2, int len) {
        if(len == 0) return true;
        if(len == 1) return s1[lo1] == s2[lo2];
        if(!isAnagram(s1, lo1, s2, lo2, len)) return false;
        //cut s1 and s2 into two parts
        for(int i = 1; i < len; ++i) {
            if(isScramble(s1, lo1, s2, lo2, i) && isScramble(s1, lo1+i, s2, lo2+i, len-i)) return true;
            if(isScramble(s1, lo1, s2, lo2+len-i, i) && isScramble(s1, lo1+i, s2, lo2, len-i)) return true;
        }
        return false;
    }

    bool isAnagram(const string& s1, int lo1, const string& s2, int lo2, int len) {
        vector<int> dict(256, 0);
        for(int i = lo1; i < lo1+len; ++i) {
            dict[s1[i]]++;
        }
        for(int i = lo2; i < lo2+len; ++i) {
            if(--dict[s2[i]] < 0) return false;
        }
        return true;
    }
};

/*
2. 3D DP solution (bottom-up), 284 ms even with adding isAnagram checking for branching.  3 indices, len, i, j
//dp[i][j][len]: whether s1[i, i+len) and s2[j, j+len) is scramble, len can be 0 to n, i, j can be 0 to n-1
len as outer loop. Special treatment when len = 1.
*/

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.size() != s2.size()) return false;
        if(s1.empty()) return true; //empty string
        int n = s1.size();
        //dp[i][j][len]: whether s1[i, i+len) and s2[j, j+len) is scramble, len can be 0 to n, i, j can be 0 to n-1
        dp.resize(n+1, vector<vector<bool> >(n, vector<bool>(n, false)));
        for(int len = 1; len <= n; ++len) {
            for(int i = 0; i+len <= n; ++i) {
                for(int j = 0; j+len <= n; ++j) {
                    if(len == 1) {
                       dp[len][i][j] = (s1[i] == s2[j]);
                       continue;
                    }
                    if(!isAnagram(s1, i, s2, j, len)) { dp[len][i][j] = 0; continue; }
                    for(int l = 1; l < len; ++l) {
                        dp[len][i][j] = ((dp[l][i][j] && dp[len-l][i+l][j+l]) || (dp[l][i][j+len-l] && dp[len-l][i+l][j]));
                        if(dp[len][i][j]) break;
                    }
                }
            }
        }
        return dp[n][0][0];
    }
    
    bool isAnagram(const string& s1, int lo1, const string& s2, int lo2, int len) {
        vector<int> dict(256, 0);
        for(int i = lo1; i < lo1+len; ++i) {
            dict[s1[i]]++;
        }
        for(int i = lo2; i < lo2+len; ++i) {
            if(--dict[s2[i]] < 0) return false;
        }
        return true;
    }

    vector<vector<vector<bool> > > dp;
};

/*
3. 3D DP solution with memoization (20ms). now the 3D vector can have three values, -1, 0, 1. -1 means uninitialized, 0 means not scramble, 1 means scramble. Need to ensure each call to scramble returns either 0 and 1 and properly sets dp[len][i][j] at the first time.
*/

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.size() != s2.size()) return false;
        if(s1.empty()) return true; //empty string
        int n = s1.size();
        //dp[i][j][len]: whether s1[i, i+len) and s2[j, j+len) is anagram, len can be 0 to s1.size, i, j can be 0 to n-1
        dp.resize(n+1, vector<vector<int> >(n, vector<int>(n, -1)));
        return isScramble(s1, 0, s2, 0, s1.size());
    }
    //memoization, always return 0 or 1
    int isScramble(const string& s1, int i, const string& s2, int j, int len) {
        int tag = dp[len][i][j];
        if(tag >= 0) return tag;

        if(len == 0) dp[len][i][j] = 1;
        else if(len == 1) dp[len][i][j] = (s1[i] == s2[j]);
        else if(!isAnagram(s1, i, s2, j, len)) dp[len][i][j] = 0;
        else {
             dp[len][i][j] = 0; //should first set to zero (for not found case)
             //cut s1 and s2 into two parts
             for(int l = 1; l < len; ++l) {
                 if( (isScramble(s1, i, s2, j, l) && isScramble(s1, i+l, s2, j+l, len-l) ) ||
                     (isScramble(s1, i, s2, j+len-l, l) && isScramble(s1, i+l, s2, j, len-l) ) ) {
                     dp[len][i][j] = 1;
                     break;
                 }
             }
        }
        return dp[len][i][j];
    }

    bool isAnagram(const string& s1, int lo1, const string& s2, int lo2, int len) {
        vector<int> dict(256, 0);
        for(int i = lo1; i < lo1+len; ++i) {
            dict[s1[i]]++;
        }
        for(int i = lo2; i < lo2+len; ++i) {
            if(--dict[s2[i]] < 0) return false;
        }
        return true;
    }

    vector<vector<vector<int> > > dp;
};


