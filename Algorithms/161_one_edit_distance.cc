/*
Given two strings S and T, determine if they are both one edit distance apart.
*/

/*
one pass solution. Two pointers scanning two arrays.
For s[i] and t[j], If found equal, move forward,
if not equal, then the rest should be the same, three cases:
a) remove s[i] and the rest matches, so we just check isSame for s[i+1, m) and t[j, n). e.g.
   abc[de]   ab[de]
     i          j
b) insert t[j] and the rest matches, so we just check isSame for s[i, m) and t[j+1, n) e.g
   ab[efg]   abd[efg]
      i        j
c) replace s[i] with t[j] and the rest matches, so we just check isSame for s[i+1, m) and t[j+1, n) e.g.
   abe[fg]   abc[fg]
     i         j

Finally, if we break out of loop, which means everything seen so far is matched. We simply check if we still have one and only one unchecked character in either one of the two arrays.

*/

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int m = s.size(), n = t.size();
        if(m - n < -1 || m -n > 1) return false;
        int i = 0, j = 0;
        while(i < m && j < n) {
            if(s[i] == t[j]) { i++; j++; }
            else return isSame(s, i+1, t, j) || isSame(s, i, t, j+1) || isSame(s, i+1, t, j+1);
        }
        return j == n-1 || i == m-1;
    }
    bool isSame(const string& s, int i, const string& t, int j) {
        int m = s.size(), n = t.size();
        while(i < m && j < n) {
            if(s[i] != t[j]) return false;
            i++; j++;
        }
        return i == m && j == n;
    }
};

