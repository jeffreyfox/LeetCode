/*
Given a string, find the length of the longest substring T that contains at most 2 distinct characters.

For example, Given s = “eceba”,

T is "ece" which its length is 3. 
*/

// Solution: use a hash table to store the counts of each character, and record the starting index of substring. Do a one-time linear search.
// Also store the count of disctinct characters and update i properly (by checking individual count of each character)
// For each character, increment the individual counts. If newly added, increment count.
// When count > 2, remove leading characters in substring (increment istart), and decrement individual counts in table. If no such character
// occurs, decrement count.
// Since the input is a string, using index table instead of unordered_map leads to better performance.

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        vector<int> dict(256, 0);
        int n = s.size();
        int count = 0; //count of disctinct characters
        int istart = 0; //start of substring
        int max_len = 0; //max length of substring
        for(int i = 0; i < n; ++i) {
            dict[s[i]]++;
            if(dict[s[i]] == 1) count++; //new entry added
            while(count > 2) { //more than 2 disctinct characters, remove some characters in the front
                dict[s[istart]]--;
                if(dict[s[istart]] == 0) count--;
                istart++;
            }
            max_len = max(max_len, i-istart+1);
        }
        return max_len;
    }
};

// A faster version with shorter lines (but less readability)
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        vector<int> dict(256, 0);
        int n = s.size();
        int count = 0; //count of disctinct characters
        int istart = 0; //start of substring
        int max_len = 0; //max length of substring
        for(int i = 0; i < n; ++i) {
            if(++dict[s[i]] == 1) count++; //new entry added
            while(count > 2) { //more than 2 disctinct characters, remove some characters in the front
                if(--dict[s[istart++]] == 0) count--;
            }
            max_len = max(max_len, i-istart+1);
        }
        return max_len;
    }
};

