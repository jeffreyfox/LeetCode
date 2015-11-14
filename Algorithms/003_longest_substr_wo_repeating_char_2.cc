/*
Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*/

// Another solution by counting the occurrences of each character, similar to problem 159.
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
         int n = s.size(); //number of records
         int istart = 0, max_len = 0;
         int count = 0;
         vector<int> dict(256);
         for(int i = 0; i < n; ++i) {
            char c = s[i];
            ++dict[c];
            while(dict[c] > 1) {
               --dict[s[istart++]];
            }
            max_len = max(max_len, i-istart+1);
         }
         return max_len;
    }
};
