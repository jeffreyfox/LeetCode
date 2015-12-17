/*
Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?
*/

/// Linear time solution by using a hash table (array indexing)
/// For unicode, we might use an unordered map (real hash table) to save memory space.

class Solution {
public:
    bool isAnagram(string s, string t) {
        int n = s.size();
        if (t.size() != n) return false;
        vector<int> cnt(256, 0);
        for (int i = 0; i < n; ++i) cnt[s[i]]++;
        for (int i = 0; i < n; ++i) {
            cnt[t[i]]--;
            if(cnt[t[i]] < 0) return false;
        }
        return true;
    }
};

// Solution 2. O(nlgn) solution using sorting.

class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};
