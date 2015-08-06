// Simplest solution: maintain a map from string (sorted) to a vector of indices who is anagram to the string.
// Process all strings, then check the map and add to result if the vector size is larger than 1

class Solution {
public:
     vector<string> anagrams(vector<string>& strs) {
        vector<string> ret;
        if (strs.empty()) return ret;
        int n = strs.size();
        if (n == 1) return ret;
        map<string, vector<int> > table;
        for (int i = 0; i < n; ++i) {
           string s = strs[i];
           sort(s.begin(), s.end());
           table[s].push_back(i);
        }
        for (map<string, vector<int> >::iterator it = table.begin(); it != table.end(); ++it) {
            if (it->second.size() > 1) {
               for (size_t i = 0; i < it->second.size(); ++i)
                   ret.push_back(strs[it->second[i]]);
            }
        }
        return ret;
    }
};
