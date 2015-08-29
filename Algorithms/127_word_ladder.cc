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

// BFS, when found a word in dictionary, remove it from dictionary.
// Length is distance + 1 !

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordDict) {
        typedef pair<string, int> Element;
        deque<Element> q; //FIFO queue for BFS
        int n = beginWord.size();
        q.push_back(make_pair(beginWord, 0));
        wordDict.erase(beginWord);
        while(!q.empty()) {
            string word = q.front().first;
            int dist = q.front().second;
            if(word == endWord) return dist+1; //found endWord, length is dist+1 !
            q.pop_front();
            string newWord = word;
            for(int i = 0; i < n; i++) { //replace each digit
                for (char c = 'a'; c <= 'z'; c++) { //try all possible ways
                    if(c == word[i]) continue;
                    newWord[i] = c;
                    if(wordDict.count(newWord)) {
                        q.push_back(make_pair(newWord, dist+1));
                        wordDict.erase(newWord); //remove it from dictionary
                    }
                }
                newWord[i] = word[i]; //revert
            }
        }
        return 0;
    }
};
