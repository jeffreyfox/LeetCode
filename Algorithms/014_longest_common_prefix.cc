/*
Write a function to find the longest common prefix string amongst an array of strings. 
*/

// Compare all strings against first string. Two nested loops. When found a mismatch, simply return the maximum length found so far.
// If no mismatch found, return full first string
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        int n = strs.size();
        if(n == 1) return strs[0];
        int ns = strs[0].size();
        for(int j = 0; j < ns; ++j) { //j loops over each string
            for(int i = 1; i < n; ++i) { //i loops over vector of strings
                if(j == strs[i].size() || strs[i][j] != strs[0][j])  //found a mismatch!
                    return strs[0].substr(0, j); //return s[0, j)
            }
        }
        return strs[0];
    }
};

// Another solution, need to break out two nested loops.
// Compare all strings against first string

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        if (n == 0) return string();
        if (n == 1) return strs[0];
        string s;
        bool stop = false;
        for (int j = 0; j < strs[0].size(); ++j) {
            stop = false;
            for (int i = 1; i < n; ++i)
                if (j == strs[i].size() || strs[i][j] != strs[0][j]) { stop = true; break; }
            if (stop) break;
            s += strs[0][j];
        }
        return s;
    }
};
