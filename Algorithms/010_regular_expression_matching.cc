/*
Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
*/

/*
Solution 1. Standard dynamic programming. Use a 2D vector dp, dp[i][j] stores whether s[0 .. i-1] matches p[0 .. j-1]. dp[i][j] can be determined by the following rules:

1. if p[j-1] is not '*', then we simply check dp[i-1][j-1] and whether s[i-1] matches p[j-1]:
           t[i-1]
t:   abc  | d   => match abc with a*bc, and d with d
p:   a*bc | d
           p[j-1]

           t[i-1]
t:   abc  | d   => match abc with a*bc, and d with .
p:   a*bc | .
           p[j-1]
thus dp[i][j] = dp[i-1][j-1] && matchHelper(s[i-1], p[j-1]);

whether matchHelper(t, p) returns true when p == '.' or p == t.

2. if p[j-1] is '*', we have two sub-cases. Let p[j-2] = x (for p to be a valid RE, '*' has to follow another character that is not '*'). Then x* can match nothing or one or more x's.
a) x* matches nothing, then we just check dp[i-1][j-2]
           t[i-1]
t:   ab    | d   => match abd with a*bd, ignore e*
p:   a*bde | *
          p[j-1]

b) x* matches at least one x, iff p[0, j-1] matches with s[0, i-2], and s[i-2] matches with x/
           t[i-1]
t:   abde  | e   => match abde with a*bde, then e with e
p:   a*bde | *
          p[j-1]

           t[i-1]
t:   abde  | e   => match abde with a*bd., then e with .
p:   a*bd. | *
          p[j-1]

thus dp[i][j] = dp[i][j-2] || (dp[i-1][j] && matchHelper(s[i-1], p[j-2])

Boundary case:
1. "" matches with "", so dp[0][0] = true
2. a non-empty p may also match "", e.g. "a*", so dp[0][j] = dp[0][j-2] && p[j-1] == '*'
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        if(p == "") return s == "";
        //s can be "", p cannot
        int m = s.size(), n = p.size();
        vector<vector<bool> > dp(m+1, vector<bool>(n+1, false)); //match[i][j]: s[0..i-1] matches p[0..j-1]
        dp[0][0] = true; // "" matches ""
        //matching p with ""
        for(int j = 1; j <= n; ++j)
            dp[0][j] = p[j-1] == '*' && dp[0][j-2];
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(p[j-1] != '*') dp[i][j] = dp[i-1][j-1] && matchHelper(s[i-1], p[j-1]);
                else dp[i][j] = dp[i][j-2] || (dp[i-1][j] && matchHelper(s[i-1], p[j-2]));
            }
        }
        return dp[m][n];
    }
    bool matchHelper(char t, char p) {
        return p == '.' || p == t;
    }
};

/*
Solution 2. Recursive solution, which takes 76ms (v.s. 20ms in solution 1).
Two pointers to scan text and pattern. When we see a pattern character, we "peek" the next character in pattern. If it is not '*', then we do normal matching, and move both forward in case of match. If next is a '*', then we either match empty string (move j two steps further, i stay put), or match one or more charaters after i if they match with p[j].
*/

class Solution {
public:
    bool matchHelper(char t, char p) {
        return p == '.' || p == t;
    }

    bool isMatch(string s, string p) {
        return isMatch(s, p, 0, 0);
    }

    bool isMatch(const string& s, const string& p, int i, int j) {
        int n = s.size(), m = p.size(); //n, i for text; m, j for pattern
        if(j == m) return i == n;
        if(j == m-1 || p[j+1] != '*') { //last char, or next is not '*'
           return matchHelper(s[i], p[j]) && isMatch(s, p, i+1, j+1);
        } else { // next character is '*'
            //first match c* with empty string
            if(isMatch(s, p, i, j+2)) return true;
            //match one or more c's
            while(i < n && matchHelper(s[i], p[j])) {
                if(isMatch(s, p, ++i, j+2)) return true;
            }
	/* //a variant of the last while loop, greedy match, but not much improvements.
	    int k = i;
            while(k < n && matchHelper(s[k], p[j])) k++;
            while(k > i) {
                if(isMatch(s, p, k--, j+2)) return true;
            }
	*/
        }
        return false;
    }
};


