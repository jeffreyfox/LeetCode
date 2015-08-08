// recursive solution. Use a helper function to check if two strings are anagram, and immediately return false if not.
// Then check every possibilities of partition:
// e.g.  a0-a4 v.s. b0-b4
// check  a0 | a1-a4 v.s. b0 | b1-b4; a0a1 | a2-a4 v.s. b0b1 | b2-b4 ... and
//        a0 | a1-a4 v.s. b0-b3 | b4; a0a1 | a2-a4 v.s. b0-b2 | b3b4 ...

class Solution {
public:
    bool isScramble(string s1, string s2) {
        int n = s1.size();
        if (n == 0) return true;
        if (!isAnagram(s1, s2)) return false;
        else if (n <= 3) return true;
        for (int k = 1; k < n; ++k) {
            if(isScramble(s1.substr(0, k), s2.substr(0, k)) && isScramble(s1.substr(k, n-k), s2.substr(k, n-k))) return true;
            if(isScramble(s1.substr(0, k), s2.substr(n-k, k)) && isScramble(s1.substr(k, n-k), s2.substr(0, n-k))) return true;
        }
        return false;
    }

    bool isAnagram(const string& s1, const string& s2) {
        vector<int> count(256, 0);
        for(int i = 0; i < s1.size(); ++i) {
            count[s1[i]]++;
        }
        for(int i = 0; i < s2.size(); ++i) {
            count[s2[i]]--;
            if(count[s2[i]] < 0) return false;
        }
        return true;
    }

};
