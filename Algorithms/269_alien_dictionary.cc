/*
There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

For example,
Given the following words in dictionary,

[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]

The correct order is: "wertf".

Note:

    You may assume all letters are in lowercase.
    If the order is invalid, return an empty string.
    There may be multiple valid order of letters, return any one of them is fine.
*/

// Build a graph containing vertices corresponding letters 'a' to 'z'. Scan the dictionary twice. First time add vertices for seen characters. Second time compare two adjacent strings and add an edge for the pair of characters. 
// Then do a topological sort, and return the result as string. During the topo-sort, also detect whether there is a cycle. If detected, immediately return to calling function which in turn returns "" to main function.
// Use the 3-color scheme in CLRS (white, grey, black) to do topo-sort and cycle detection in one pass.

class Graph {
public:
    Graph()  {
        vertices.resize(26, false);
        adj.resize(26);
        color.resize(26, 0); //0: unvisited, 1: on stack, 2: finished
	hasCycle = false;
    }
    void addVertex(char c) {
        vertices[c-'a'] = true; 
    }
    void addEdge(char c1, char c2) {
        adj[c1-'a'].push_back(c2-'a');
    }

    string topoSort() {
        string s;
        for(int v = 0; v < 26; ++v) {
            if(vertices[v] && color[v] == 0) {
                dfs(v, s);
                if(hasCycle) return "";
            }
        }
        reverse(s.begin(), s.end());
        return s;
    }

    void dfs(int v, string& s) {
        if(hasCycle) return;
        color[v] = 1;
        for(auto w : adj[v]) {
            if(color[w] == 0) dfs(w, s);
            else if(color[w] == 1) { hasCycle = true; return; }
        }
        color[v] = 2;
        //after we are done with v, push back to s.
        s.push_back(v+'a');
    }

private:
    vector<bool> vertices; //vertices (26)
    vector<vector<int> > adj; //adjacency lists 
    vector<int> color; // whether vertices are on stack
    bool hasCycle;
};

class Solution {
public:
    string alienOrder(vector<string>& words) {
        if(words.empty()) return "";
        int n = words.size();
        Graph g;
        for(int i = 0; i < n; ++i)
            for(char c : words[i])
                 g.addVertex(c);

        for(int i = 1; i < n; ++i) {
           int jmax = min(words[i].size(), words[i-1].size());
           for(int j = 0; j < jmax; ++j) {
               if(words[i-1][j] != words[i][j]) { g.addEdge(words[i-1][j], words[i][j]); break;}
           }
        }
        return g.topoSort();
    }
};

