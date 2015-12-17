/*
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.
*/

//Use two maps, one mapping s to t and the other backwards. Use indices array to mimic map for fast access. 

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.size() != t.size()) return false;
        if(s.empty()) return true;
        int n = s.size();
        vector<int> s2t(256, -1), t2s(256, -1);
        for(int i = 0; i < n; ++i) {
            int a = s[i], b = t[i];
            if(s2t[a] == -1 && t2s[b] == -1) { //new entry, insert to both maps
                s2t[a] = b; t2s[b] = a;
            } else if(s2t[a] == b && t2s[b] == a) continue; //matches, continue
            else return false; //other cases, simply return false.
        }
        return true;
    }
};

