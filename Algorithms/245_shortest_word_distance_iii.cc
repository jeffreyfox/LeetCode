/*
This is a follow up of Shortest Word Distance. The only difference is now word1 could be the same as word2.

Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

word1 and word2 may be the same and they represent two individual words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “makes”, word2 = “coding”, return 1.
Given word1 = "makes", word2 = "makes", return 3.

Note:
You may assume word1 and word2 are both in the list.
*/

// Solution 1. Similar to 243 with additional lines to take care of case where word1 == word2.
class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        int index(-1), mind = INT_MAX, n = words.size();
        for(int i = 0; i < n; i++) {
            const string& w = words[i];
            if(w == word1 || w == word2) {
                if(word1 == word2) {
                    if(index != -1) mind = min(mind, i-index);
                } else {
                    if(index != -1 && words[index] != w) mind = min(mind, i-index);
                }
                index = i;
            }
        }
        return mind;
    }
};

// Solution 2. Simplified control logic

class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        int index(-1), mind = INT_MAX, n = words.size();
        for(int i = 0; i < n; i++) {
            const string& w = words[i];
            if(w == word1 || w == word2) {
                if(index != -1 && (word1 == word2 || words[index] != w)) mind = min(mind, i-index);
                index = i;
            }
        }
        return mind;
    }
};
