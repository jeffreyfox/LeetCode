/*
Given two words (beginWord and endWord), and a dictionary, find the length of shortest transformation sequence from beginWord to endWord, such that:

    Only one letter can be changed at a time
    Each intermediate word must exist in the dictionary

For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]

As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:

    Return 0 if there is no such transformation sequence.
    All words have the same length.
    All words contain only lowercase alphabetic characters.

*/

/* 
=== Solution 1 ===
One-way BFS from beinWord to endWord. Create a new dict to track words already visited.
BFS with two sets, one for current level, one for next level, and in the end of each iteration update accordingly
Systematically trying the new word by altering one character of the new word. Do not create a new string, rather change the character in-place and
revert back to original afterwards.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict;
        for (const auto &w : wordList) dict.insert(w);
        
        int counter = 1;
        unordered_set<string> seen;
        vector<string> curr, next;
        curr.push_back(beginWord);     
        
        while (!curr.empty()) {
            for (const auto &word : curr) {
                // try all combinations
                string newWord = word;
                for (int i = 0; i < newWord.size(); ++i) {
                    char tmp = newWord[i];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == tmp) continue;
                        newWord[i] = c;                        
                        if (!dict.count(newWord)) continue;
                        if (seen.count(newWord)) continue;
                        
                        if (newWord == endWord) return counter+1;
                        
                        seen.insert(newWord);
                        next.push_back(newWord);
                    }
                    newWord[i] = tmp;
                }
            }
            curr = next;
            next.clear();
            counter++;
        }
        return 0;
    }
};

/*
=== Solution 2 ===
Bi-directional BFS to reduce search space. Start from two ends (begin/end), and only do BFS from the side with smaller search space. 
When we find one string in the search front that belongs to the front of the other side, we have "connected" the two sides.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
       unordered_set<string> beginSet, nextSet, endSet;
       unordered_set<string> unvisited = wordList;
       int wl = beginWord.size();

       unvisited.erase(beginWord);
       unvisited.erase(endWord);

       beginSet.insert(beginWord);
       endSet.insert(endWord);
       int level = 2;

       while(!beginSet.empty()) {
           //for(unordered_set<string>::iterator it = beginSet.begin(); it != beginSet.end(); ++it) {
           for(auto wd : beginSet) {
               for(int i = 0; i < wl; ++i) {
                   char c = wd[i];
                   for(char ch = 'a'; ch <= 'z'; ++ch) {
                       if(ch == c) continue;
                       wd[i] = ch;
                      if(endSet.count(wd)) return level;
                       if(unvisited.count(wd))  {
                           nextSet.insert(wd);
                           unvisited.erase(wd);
                       }
                   }
                   wd[i] = c; //revert back
               }
           }
           beginSet.swap(nextSet);
           nextSet.clear();
           level++;
           if(beginSet.size() > endSet.size()) beginSet.swap(endSet);
       }
       return 0;
    }
};

/*
=== Solution 4 ===
Bidirectional BFS, recursive solution (64ms!)
*/
class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        unordered_set<string> unvisited = wordList;
        unvisited.erase(beginWord);
        unvisited.erase(endWord);
        unordered_set<string> forwardSet, backwardSet;
        forwardSet.insert(beginWord);
        backwardSet.insert(endWord);
        return ladderLengthUtil(forwardSet, backwardSet, unvisited, 2);
    }
    int ladderLengthUtil(unordered_set<string>& forwardSet, unordered_set<string>& backwardSet, unordered_set<string>& unvisited, int level) {
        if(forwardSet.empty()) return 0;
        if(forwardSet.size() > backwardSet.size()) return ladderLengthUtil(backwardSet, forwardSet, unvisited, level);
        unordered_set<string> next;
        for(auto word : forwardSet) {
            //try all posssibilities
            for(auto it = word.begin(); it != word.end(); ++it) {
                char tmp = *it;
                for(*it = 'a'; *it != 'z'; ++(*it)) {
                    if(*it == tmp) continue;
                    if(backwardSet.count(word)) return level;
                    else if(unvisited.count(word)) { //not visited
                        unvisited.erase(word);
                        next.insert(word);
                    }
                }
                *it = tmp; //revert back
            }
        }
        return ladderLengthUtil(next, backwardSet, unvisited, level+1);
    }
};

