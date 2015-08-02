/// Linear time solution by using a hash table (array indexing)

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
