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

// Build a graph containing vertices corresponding letters 'a' to 'z'.
// Scan the dictionary twice. First time add vertices for seen characters. Second time compare two adjacent strings and add an edge for the pair of characters. 
// Then do a topological sort, and return the result as string. During the topo-sort, also detect whether there is a cycle.
// If detected, immediately return to calling function which in turn returns "" to main function.
// Use two vectors to track visited and on-stack states. Alternatively, we can use the 3-color scheme in CLRS (white, grey, black).
// Needs to handle the corner case where input can't be lexi sorted, e.g. ["abc", "ab"].

class Graph {
public:
    Graph() : has_cycle(false) {
        adj.resize(26);
        in_dict.resize(26, false);
        visited.resize(26, false);
        on_stack.resize(26, false);
    }

    void addVertex(char c) {
        in_dict[c - 'a'] = true;
    }

    void addEdge(char c1, char c2) {
        int idx1 = c1 - 'a';
        int idx2 = c2 - 'a';
        adj[idx1].push_back(idx2);
        in_dict[idx1] = true;
        in_dict[idx2] = true;
    }
    
    string topoSort() {
        for (int i = 0; i < 26; ++i) {
            dfs(i);
            if (has_cycle) return "";
        }
        string result;
        while (!postorder.empty()) {
            result.append(1, postorder.top() + 'a');
            postorder.pop();
        }
        return result;
    }

private:    
    void dfs(int i) {
        if (has_cycle) return;
        if (!in_dict[i] || visited[i]) return;
        if (on_stack[i]) {
            has_cycle = true;
            return;
        }
        
        on_stack[i] = true;
        for (auto j : adj[i]) {
            dfs(j);
            if (has_cycle) return;
        }
       
        visited[i] = true;
        on_stack[i] = false;
        postorder.push(i);
    }

    bool has_cycle;
    vector<vector<int>> adj;
    vector<bool> in_dict;
    vector<bool> visited;
    vector<bool> on_stack;
    stack<int> postorder;
};


class Solution {
public:
    string alienOrder(vector<string>& words) {
        Graph graph;
        int n = words.size();
        for (const auto &w : words) {
            for (const char c : w) {
                graph.addVertex(c);
            }
        }

        for (int i = 0; i < n-1; ++i) {            
            const string &word1 = words[i];
            const string &word2 = words[i+1];
            
            // Find order from the two words
            int min_len = min(word1.size(), word2.size());
            int j = 0;
            while (j < min_len) {
                if (word1[j] != word2[j]) {
                    graph.addEdge(word1[j], word2[j]);
                    break;
                }
                j++;
            }
            // corner case: ["abc", "ab"] => ""
            if (j == min_len && word1.size() > word2.size()) return "";
        }
            
        return graph.topoSort();
    }
};
