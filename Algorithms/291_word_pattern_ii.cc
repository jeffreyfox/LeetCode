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
// Each time grab a character in pattern, and try to match all possibilities in str. Use two maps to store the current mapping relations between the character and str. We need both forward (pat2txt) and backward mapping (txt2pat). 
// The function dfs starts matching pattern[i, end) with str[j, end). If i or j reaches end, we terminate properly.
// Then we take a character from pattern[i], and try to match any strings starting at j in str. There are several cases:
// 1. If pattern[i] is already found in the pat2txt map, then we have to match the same entry for str[j, end). We extract the same size from str (possibly out of str' range, which we need to properly take care of), and compare with the entry pat2txt. If matches we continue to next step by matching pattern[i+1, end) with str[j+len, end). Otherwise, we simply return false.
// 2. If pattern[i] is not found in pat2txt map, then we try all possibilities from str[j, end), i.e. str[j, j+1), str[j, j+2) ...
// For each trials, we need to check if they are already assigned to a mapping formula in txt2pat. If yes, we need to skip it (to ensure bijection relation). Otherwise, we make this the current mapping trial, and insert it to the two maps, and move to next step. After we are done, we erase the entries in the two maps to retrace.
// During the search, whenever we find a valid match, we return true immediately.
// Caveats:
//  if(j+len > n || str.substr(j, len) != sub), the first condition is necessary to avoid going out of bounds!

class Solution {
public:
    bool wordPatternMatch(string pattern, string str) {
        if(pattern.empty()) return str.empty();
        if(str.empty()) return pattern.empty();
        return dfs(pattern, 0, str, 0);
    }

    bool dfs(const string& pattern, int i, const string& str, int j) {
        int m = pattern.size(), n = str.size();
        if(i == m || j == n) return i == m && j == n;
        //read one pattern character
        char c = pattern[i];
        if(!pat2txt.count(c)) { //new character
            //try all possibilities from str[j, end) if that is not already in txt2pat
            for(int len = 1; len <= n-j; ++len) {
                string sub = str.substr(j, len);
                if(txt2pat.count(sub)) continue;
                pat2txt[c] = sub; //insert
                txt2pat[sub] = c; //insert
                if(dfs(pattern, i+1, str, j+len)) return true;
                pat2txt.erase(c); //retrace
                txt2pat.erase(sub); //retrace
            }
        } else { //already found mapping
            string sub = pat2txt[c];
            int len = sub.size();
            if(j+len > n || str.substr(j, len) != sub) return false; //not found match
            if(dfs(pattern, i+1, str, j+len)) return true; //found match, move to next step
        }
        return false; //finished matching
    }

    unordered_map<char, string> pat2txt;
    unordered_map<string, char> txt2pat;
};

