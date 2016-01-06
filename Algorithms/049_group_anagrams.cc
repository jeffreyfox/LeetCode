/*
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:

    For the return value, each inner list's elements must follow the lexicographic order.
    All inputs will be in lower-case.
*/

// Solution 1. Using a hash table to store the already found anagrams. Use the sorted string as the key. 68ms.
// For each string in strs, if found in table, then insert to approapriate positions, otherwise, add a new vector to the result, and push the string to that vector.
// Finally, sort each sub-vector

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if(strs.empty()) return result;
        unordered_map<string, int> dict;

        for(int i = 0; i < strs.size(); ++i) {
            string s = strs[i];
            sort(s.begin(), s.end());
            if(dict.count(s)) { //found anagrams
                result[dict[s]].push_back(strs[i]);
            } else { //new entry
                dict[s] = result.size();
                result.push_back(vector<string>(1, strs[i]));
            }
        }
        for(int i = 0; i < result.size(); ++i) {
            sort(result[i].begin(), result[i].end());
        }
        return result;
    }
};

// Solution 2. 400ms. Not a very efficient solution.
// First sort the strs array by a customized compare function (compare each string's sorted forms). After this step all anagrams are ajacent to each other. Next step scan the array and group anagrams using the isAnagram function. Still need to sort each group in the end.

bool compare(const string& s, const string& t) {
    string ss = s, tt = t;
    sort(ss.begin(), ss.end());
    sort(tt.begin(), tt.end());
    return ss < tt;
}

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if(strs.empty()) return result;
        sort(strs.begin(), strs.end(), compare);

        for(int i = 0; i < strs.size(); ++i) {
            if(i == 0 || !isAnagram(strs[i], strs[i-1]))
                result.push_back(vector<string>());
            result.back().push_back(strs[i]);
        }
        for(int i = 0; i < result.size(); ++i) {
            sort(result[i].begin(), result[i].end());
        }
        return result;
    }
    bool isAnagram(const string& s, const string& t) {
        if(s.size() != t.size()) return false;
        int n = s.size();
        if(n == 0) return true;
        if(n == 1) return s == t;
        vector<int> dict(26, 0);
        for(auto c : s) dict[c-'a']++;
        for(auto c : t) {
            if(--dict[c-'a'] < 0) return false;
        }
        return true;
    }
};

// Solution 3. TLE. Brute force solution, very inefficient.
// One pass. Construct result as we scan strs, for each string, linearly scan all anagram groups in results. Compare the string with the first entry of the anagram group. If found equal, insert to this group. Otherwise, append a new group to end of results and insert the string to this group.

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if(strs.empty()) return result;
        for(auto s : strs) {
            bool hasAnagram = false;
            for(int i = 0; i < result.size(); ++i) {
                if(isAnagram(result[i][0], s)) {
                    result[i].push_back(s);
                    hasAnagram = true;
                    break;
                }
            }
            if(!hasAnagram) result.push_back(vector<string>(1, s));
        }
        for(auto s : result) {
            sort(s.begin(), s.end());
        }
        return result;
    }
    bool isAnagram(const string& s, const string& t) {
        if(s.size() != t.size()) return false;
        int n = s.size();
        if(n == 0) return true;
        if(n == 1) return s == t;
        vector<int> dict(26, 0);
        for(auto c : s) dict[c-'a']++;
        for(auto c : t) {
            if(--dict[c-'a'] < 0) return false;
        }
        return true;
    }
};



