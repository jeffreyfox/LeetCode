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
One-way BFS from beinWord to endWord. Do not remove elements from the original dictionary! Rather create a new one (unvisited) and remove from it.
Systematically trying the new word by altering one character of the new word. Do not create a new string, rather change the character in-place and revert back to original afterwards.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
       deque<pair<string, int> > q;
       unordered_set<string> unvisited = wordList;
       int wl = beginWord.size();

       q.push_back(make_pair(beginWord, 1));
       unvisited.erase(beginWord); //remove beginWord to unvisited
       unvisited.insert(endWord); //insert beginWord to unvisited
       while(!q.empty()) {
           string wd = q.front().first;
           int level = q.front().second;
           if(wd == endWord) return level;
           q.pop_front();
           for(int i = 0; i < wl; ++i) {
               char c = wd[i];
               for(char ch = 'a'; ch <= 'z'; ++ch) {
                   if(ch == c) continue;
                   wd[i] = ch;
                   if(unvisited.count(wd))  {
                       q.push_back(make_pair(wd, level+1));
                       unvisited.erase(wd);
                   }
               }
               wd[i] = c; //revert back
           }
       }

       return 0;
    }
};

/*
=== Solution 2 ===
BFS with two sets, one for current level, one for next level, and in the end of each iteration swap the two.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
       vector<string> current, next;
       int level = 1;
       unordered_set<string> unvisited = wordList;
       int wl = beginWord.size();

       unvisited.erase(beginWord);
       unvisited.insert(endWord);

       current.push_back(beginWord);
       
       while(!current.empty()) {
           for(vector<string>::iterator it = current.begin(); it != current.end(); ++it) {
               string wd = *it;
               for(int i = 0; i < wl; ++i) {
                   char c = wd[i];
                   for(char ch = 'a'; ch <= 'z'; ++ch) {
                       if(ch == c) continue;
                       wd[i] = ch;
                       if(wd == endWord) return level+1;
                       if(unvisited.count(wd))  {
                           next.push_back(wd);
                           unvisited.erase(wd);
                       }
                   }
                   wd[i] = c; //revert back
               }
           }
           current.swap(next);
           next.clear();
           level++;
       }
       return 0;        
    }
};

/*
=== Solution 3 ===
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
