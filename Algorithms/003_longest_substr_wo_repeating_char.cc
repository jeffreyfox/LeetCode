// Solution 1 using sliding window.
// Maintain two pointers for the start and end of the sliding window, and a set of characters in the window.
// Scan from left to right, for the new character
// (a) if it is not in the set, insert to set
// (b) otherwise, we move the start pointer to the right until we see the character. We then move the start one step further to point to the new start.
// The length is simply end - start + 1. Each time we update the max length with this.

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int i = 0, j = 0;
        int max_length = 0;
        unordered_set<char> dict;
        for (int j = 0; j < s.size(); ++j) {
            const auto c = s[j];
            if (dict.count(c)) {
                while (s[i] != c) {
                    dict.erase(s[i]);
                    i++;                    
                }
                i++;
            }
            dict.insert(c);
            max_length = max(max_length, j-i+1);
        }
        return max_length;
    }
};

// Solution 2 similar to solution 1. Use a map to track the count of each character.
// Similar to above, except for the logic to move the left pointer. We check the current count of the character ponited by the end pointer. We stop if the count
// is 1. This way we don't need to move one step further.
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int i = 0, j = 0;
        int max_length = 0;
        unordered_map<char, int> count;
        for (int j = 0; j < s.size(); ++j) {
            const auto c = s[j];
            count[c] ++;
            while (count[c] > 1) {
                count[s[i]] --;
                i++;
            }
            max_length = max(max_length, j-i+1);
        }
        return max_length;
    }
};

// Solution 3, sliding window optimized (no nested while loop). Use a map to store the position of each character. Scan from left to right,
// and maintain a map to store characters already seen and its last position, update length each time.
// Use a pointer (i) to store the current front of substring
// When a character is not in the map, insert it to map; 
// When a character is found, move i to one character to the right of it. The caveat is that the character found might already be outside of the sliding window
// So we need to check the position relative to the current start of the window (i).

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int i = 0, j = 0;
        int max_length = 0;
        unordered_map<char, int> pos;
        for (int j = 0; j < s.size(); ++j) {
            const auto c = s[j];
            if (pos.count(c)) {
                i = max(pos[c]+1, i);               
            }   
            pos[c] = j;
            max_length = max(max_length, j-i+1);
        }
        return max_length;
    }
};
