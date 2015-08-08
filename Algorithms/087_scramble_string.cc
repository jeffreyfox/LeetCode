/*
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t

To scramble the string, we may choose any non-leaf node and swap its two children.
For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t

We say that "rgeat" is a scrambled string of "great".
Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a

We say that "rgtae" is a scrambled string of "great".
Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1. 
*/

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
