/*
Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

    Only one letter can be changed at a time
    Each intermediate word must exist in the word list

For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Return

  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]

Note:

    All words have the same length.
    All words contain only lowercase alphabetic characters.
*/

/*
https://leetcode.com/discuss/41689/88ms-accepted-solution-with-68ms-word-ladder-88ms-word-ladder

=== Solution 1 ===
Usual BFS, do not change wordList, rather create a new set (unvisited) and operate on it.
Create a predecessor subgraph of the BFS search (each node can have multiple parents, so use a vector for the parent field). The tree structure is stored in the map<string, vector<string> structure called predecessors.
After the map is built, traverse the map from end to begin and reconstruct the ladders. 
*/
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        vector<vector<string> > result;
        int lword = beginWord.size();
        unordered_set<string> unvisited = wordList;
        unvisited.erase(beginWord);
        unvisited.insert(endWord);
        unordered_set<string> current, next;
        unordered_map<string, vector<string> > predecessors; //predecessor map
        current.insert(beginWord);
        while(!current.empty()) {
            for(auto wd : current) {
                if(wd == endWord) break; //finishes
                unvisited.erase(wd);
                for(int i = 0; i < lword; ++i) {
                    char tmp = wd[i];
                    for(char c = 'a'; c <= 'z'; ++c) {
                        if(c == tmp) continue;
                        wd[i] = c;
                        if(unvisited.count(wd) && current.count(wd) == 0) { //belongs to wordList, and unvisited
                            next.insert(wd);
                            string owd = wd;
                            owd[i] = tmp;
                            predecessors[wd].push_back(owd);
                        }
                    }
                    wd[i] = tmp;
                }
            }

            current.swap(next);
            next.clear();
        }

        //now we have predecessor map, we can build the result using dfs
        vector<string> path;
        dfs(endWord, beginWord, predecessors, path, result);
        return result;
    }
    
    void dfs(const string& word, const string& beginWord, unordered_map<string, vector<string> >& predecessors, vector<string>& path, vector<vector<string> >& result) {
        path.insert(path.begin(), word);
        if(word == beginWord) {
            result.push_back(path);
            path.erase(path.begin());
            return;
        }
        for(auto it : predecessors[word]) {
            dfs(it, beginWord, predecessors, path, result);
        }
        path.erase(path.begin());
    }
};

/*
=== Solution 2 ===
Two way BFS. Instead of storing predecessor, store children map (we can in principle store two predecessor maps for the two direction, but one is much simpler). Since we are going to have multiple predecessor or children, storing children map does not increase the memory usage. Also, children graph makes it easy to construct the ladder path (array push back instead of inserting to front).

Use a tag "found" to check if found. Only construct the ladder when found is set as true.

Use a tag "forward" to keep track of search direction (forwards or backwards)
*/

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        vector<vector<string> > result;
        
        unordered_set<string> current, opposite, next;
        unordered_map<string, vector<string> > children; //children map
        unordered_set<string> unvisited = wordList;

        unvisited.erase(beginWord);
        unvisited.erase(endWord);

        current.insert(beginWord);
        opposite.insert(endWord);
        bool forward = true;
        bool found = false;

        while(!current.empty()) {
            for(auto word : current) unvisited.erase(word);
            for(auto word : current) {
                //unvisited.erase(word);
                string newWord = word;
                for(auto it = newWord.begin(); it != newWord.end(); ++it) {
                    char tmp = *it;
                    for(*it = 'a'; (*it) <= 'z'; ++(*it)) {
                        if(*it == tmp) continue;
                        if(opposite.count(newWord)) { //found word in opposite search front
                            found = true;
                            if(forward) children[word].push_back(newWord);
                            else children[newWord].push_back(word);
                        } else if(unvisited.count(newWord)/* && !current.count(newWord)*/) { //belongs to wordList, and unvisited
                            next.insert(newWord);
                            if(forward) children[word].push_back(newWord);
                            else children[newWord].push_back(word);
                        }
                    }
                    *it = tmp; //revert
                }
            }
            if(found) break;
            
            current.swap(next);
            next.clear();
            if(current.size() > opposite.size()) { 
                current.swap(opposite);
                forward = !forward;
            }
        }
        //only proceed when found
        if(found) {
            vector<string> path;
            dfs(beginWord, endWord, children, path, result);
        }
        return result;
    }

    void dfs(const string& beginWord, const string& endWord, unordered_map<string, vector<string> >& children, vector<string>& path, vector<vector<string> >& result) {
        path.push_back(beginWord);
        if(beginWord == endWord) {
           result.push_back(path);
           path.pop_back();
           return;
        }
        for(auto it : children[beginWord]) {
            dfs(it, endWord, children, path, result);
        }
        path.pop_back();
    }
};

/*
=== Solution 3 ===
Bi-directional BFS, use recursive to build children graph, rather than interative. 
*/

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        vector<vector<string> > result;
        
        unordered_set<string> current, opposite;
        unordered_map<string, vector<string> > children; //children map
        unordered_set<string> unvisited = wordList;

        unvisited.erase(beginWord);
        unvisited.erase(endWord);

        current.insert(beginWord);
        opposite.insert(endWord);
        bool found = findLadders(current, opposite, unvisited, children, true);
        
        if(found) {
            vector<string> path;
            dfs(beginWord, endWord, children, path, result);
        }
        return result;
    }

    bool findLadders(unordered_set<string>& current, unordered_set<string>& opposite, unordered_set<string>& unvisited, unordered_map<string, vector<string> >& children, bool forward) {
        if(current.empty()) return false; 
        if(current.size() > opposite.size()) return findLadders(opposite, current, unvisited, children, !forward); //reverse direction
        unordered_set<string> next;
        bool found = false;
        for(auto word : current) unvisited.erase(word); //first erase all words in current from unvisited (avoid double searching)
        for(auto word : current) {
            string newWord = word;
            for(auto it = newWord.begin(); it != newWord.end(); ++it) {
                char tmp = *it;
                for(*it = 'a'; (*it) <= 'z'; ++(*it)) {
                    if(*it == tmp) continue;
                    if(opposite.count(newWord)) { //found word in opposite search front
                        found = true;
                        if(forward) children[word].push_back(newWord);
                        else children[newWord].push_back(word);
                    } else if(unvisited.count(newWord)) { //belongs to wordList, and unvisited
                        next.insert(newWord);
                        if(forward) children[word].push_back(newWord);
                        else children[newWord].push_back(word);
                    }
                }
                *it = tmp; //revert
            }
        }
        
        if(found) return true; //stop here
        else return findLadders(next, opposite, unvisited, children, forward);
    }

    void dfs(const string& beginWord, const string& endWord, unordered_map<string, vector<string> >& children, vector<string>& path, vector<vector<string> >& result) {
        path.push_back(beginWord);
        if(beginWord == endWord) {
           result.push_back(path);
           path.pop_back();
           return;
        }
        for(auto it : children[beginWord]) {
            dfs(it, endWord, children, path, result);
        }
        path.pop_back();
    }
};
