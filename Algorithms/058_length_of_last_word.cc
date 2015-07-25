// Two pointers, i and j. Scan from right to left

class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.size();
        //scan from right end to left, find first non-space character
        int i = n-1;
        while (i >= 0 && s[i] == ' ') i--;
        if (i < 0) return 0;
        //scan from i to left, find first space character
        int j = i;
        while(j >= 0 && s[j] != ' ') j--;
        return i-j;
    }
};
