/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

Examples:

    pattern = "abab", str = "redblueredblue" should return true.
    pattern = "aaaa", str = "asdasdasdasd" should return true.
    pattern = "aabb", str = "xyzabcxzyabc" should return false.

Notes:
You may assume both pattern and str contains only lowercase letters. 
*/

// Backtracking solution using recursive calls.
// The recursive function recurse() starts operating at pattern[i, end) and s[j, end)
// It takes pattern[i] and tries to match all possible susbstrings of s[j, end).
// Return early if bijection mapping is violated.

class Solution {
public:
    bool wordPatternMatch(string pattern, string s) {
        return recurse(pattern, s, 0, 0);
    }
    
    bool recurse(string pattern, string s, int i, int j) {
        if (i == pattern.size() && j == s.size()) return true;
        if (i == pattern.size() || j == s.size()) return false;
        const char c = pattern[i];
        if (pat2str.count(c)) {
            const string ss = pat2str[c];
            if (s.substr(j, ss.size()) == ss) {
                return recurse(pattern, s, i+1, j + ss.size());
            } else {
                return false;
            }
        }
        // match pattern[i] with some substring of s[j..end)
        for (int len = 1; len <= s.size() - j; ++len) {
            const string ss = s.substr(j, len);
            // ss is already matched to a character
            if (str2pat.count(ss)) continue;
            pat2str[c] = ss;
            str2pat[ss] = c;
            if (recurse(pattern, s, i+1, j+len)) return true;
            // backtrack
            pat2str.erase(c);
            str2pat.erase(ss);
        }
        return false;
    }
    
private:
    unordered_map<char, string> pat2str;
    unordered_map<string, char> str2pat;
};

