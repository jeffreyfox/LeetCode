/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Examples:

    pattern = "abba", str = "dog cat cat dog" should return true.
    pattern = "abba", str = "dog cat cat fish" should return false.
    pattern = "aaaa", str = "dog cat cat dog" should return false.
    pattern = "abba", str = "dog dog dog dog" should return false.

Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space. 
*/

// Use two dictionaries to record the bijection relation between pattern (char) and words (string). Standard DFS.
// Caveats: be careful of the index bounds for exiting dfs. Should be i >= m, not i == m.
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        return dfs(pattern, str, 0, 0);
    }
    bool dfs(const string& pattern, const string& str, int i, int j) {
        int m = pattern.size(), n = str.size();
        if(i >= m && j >= n) return true; //both reaches end at the same time
        if(i >= m || j >= n) return false; //only one reaches end
        char c = pattern[i];
        int k = j;
        while(k < n && str[k] != ' ') k++;
        string s = str.substr(j, k-j);
        unordered_map<char, string>::iterator it1 = pat2word.find(c);
        unordered_map<string, char>::iterator it2 = word2pat.find(s);
        if(it1 == pat2word.end() && it2 == word2pat.end()) { //not found
            pat2word[c] = s; word2pat[s] = c; //insert
            return dfs(pattern, str, i+1, k+1);
        } else if(it1 == pat2word.end() || it2 == word2pat.end()) { //not bijection
            return false;
        } else if(it1->second == s && it2->second == c) {
            return dfs(pattern, str, i+1, k+1);
        } else return false;
    }
    unordered_map<char, string> pat2word;
    unordered_map<string, char> word2pat;
};

