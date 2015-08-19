/*
Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*/

// Solution 1, use a map (slow). Scan from left to right, and maintain a map to store characters already seen and its last position, update length each time.
// Use a pointer (i) to store the current front of substring
// When a character is not in the map, insert it to map; 
// When a character is found and its index is within i and j, then move i to one character to the right of it. 

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        map<char, int> pos;
        int max_len(0);
        for(int i = 0, j = 0; j < s.size(); ++j) {
            char c = s[j];
            if(pos.count(c) > 0 && pos[c] >= i) {
                 i = pos[c]+1;
            }
            pos[c] = j;
            max_len = max(max_len, j-i+1);
        }
        return max_len;
    }
};
