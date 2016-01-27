/*
Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.

Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.
*/

// Solution 1. Keep two indices, one for each word (20ms)
// optimizations: do not use std::min() function, also prestore the word.size() as n

class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int j1(-1), j2(-1), mind = INT_MAX, n = words.size();
        for(int i = 0; i < n; i++) {
            const string& w = words[i];
            if(w == word1) {
                j1 = i;
                if(j2 >= 0 && mind > j1-j2) mind = j1-j2;
            } else if(w == word2) {
                j2 = i;
                if(j1 >= 0 && mind > j2-j1) mind = j2-j1;
            }
        }
        return mind;
    }
};

// Solution 2. Use just one index, before assigning the new index, check the difference with previous, also need to check the current word is the same as last word
class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int index(-1), mind = INT_MAX, n = words.size();
        for(int i = 0; i < n; i++) {
            if(words[i] == word1 || words[i] == word2) {
                if(index != -1 && words[index] != words[i]) { //not the same word
                    mind = min(mind, i-index);
                }
                index = i;
            }
        }
        return mind;
    }
};

