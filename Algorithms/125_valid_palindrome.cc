// Two pointers, O(n) solution.
// ignore cases, so use isSame function to check
// isAlphaNumeric checks whether character is alpha-numeric
class Solution {
public:
    bool isPalindrome(string s) {
        if(s.empty()) return true;
        int n = s.size();
        int i(0), j(n-1);
        while (i < j) {
            if (!isAlphaNumeric(s[i])) i++;
            else if (!isAlphaNumeric(s[j])) j--;
            else if (!isSame(s[i], s[j])) return false;
            else {i++; j--; } //equal, move on
        }
        return true;
    }
    bool isAlphaNumeric(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }
    bool isSame(char c1, char c2) {
        if (c1 == c2) return true;
        if (c1 >= 'A' && c1 <= 'Z') return c2 == c1 + 32;
        if (c1 >= 'a' && c1 <= 'z') return c2 == c1 - 32;
    }
};
