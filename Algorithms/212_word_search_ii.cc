/*
Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =

[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]

Return ["eat","oath"].

Note:
You may assume that all inputs are consist of lowercase letters a-z.

click to show hint.

You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?

If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: Implement Trie (Prefix Tree) first.
*/

/*
Use a Trie data-structure. 
 Perform dfs on the board, construct the string formed by the path, see if it is contained as prefix in the Trie, if not, then stop searching. This is the essense of using Trie to speed up search.
 Caveats:
1. in trie element removal, do not remove root.
2. need to avoid duplicated entries in the return array, solution 1 erases the found entries in the Trie, solution 2 implements a found() function to check if the solution is in the array or not.
3. When found a match, need to continue searching! Do not simply return!
*/

// Solution 1.
class Trie {
public:
    struct Node {
        bool isEnd;
        vector<Node*> link;
        Node() : isEnd(false) {
            link.resize(26, NULL);
        }
    };

    Trie() {
        head = new Node();
    }

    ~Trie() {
        eraseNode(head);
    }
    void insert(const string& s) {
        insertUtil(head, s, 0);
    }

    bool exist(const string& s) {
        Node *node = find(head, s, 0);
        return node != NULL && node->isEnd;
    }
    bool existPrefix(const string& s) {
        Node *node = find(head, s, 0);
        return node != NULL;
    }
    void erase(const string& s) {
        eraseUtil(head, s, 0);
    }
private:
    void insertUtil(Node* node, const string& s, int k) {
        if(k == s.size()) { node->isEnd = true; return; }
        int i = s[k] - 'a';
        if(node->link[i] == NULL) node->link[i] = new Node();
        insertUtil(node->link[i], s, k+1);
    }

    Node* eraseUtil(Node* node, const string& s, int k) {
        if(node == NULL) return NULL;
        if(k == s.size()) {
            node->isEnd = false;
        } else {
            int c = s[k] - 'a';
            node->link[c] = eraseUtil(node->link[c], s, k+1);
        }
        if(node != head && !hasLinks(node) && !node->isEnd) {
            delete node; //no nodes below it
            node = NULL;
        }
        return node;
    }
    bool hasLinks(Node* node) {
        if(node == NULL) return false;
        for(int i = 0; i < 26; ++i) 
            if(node->link[i]) return true;
        return false;
    }
    Node* find(Node* node, const string& s, int k) {
        if(node == NULL || k == s.size()) return node;
        int i = s[k] - 'a';
        return find(node->link[i], s, k+1);
    }
    void eraseNode(Node* node) {
        if(!node) return;
        for(int i = 0; i < 26; ++i) eraseNode(node->link[i]);
        delete node;
    }
    Node* head;
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        if(board.empty() || board[0].empty()) return result;
        int m = board.size(), n = board[0].size();
        string tmp;
        for(auto it : words) t.insert(it);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                dfs(board, i, j, tmp, result);
            }
        }
        return result;
    }

    void dfs(vector<vector<char>>& board, int i, int j, string& tmp, vector<string>& result) {
        int m = board.size(), n = board[0].size();
        if(i < 0 || i >= m || j < 0 || j >= n) return; //illegal position
        if(board[i][j] == '*') return; //visited
        char c = board[i][j];
        tmp = tmp + c;
        if(t.exist(tmp)) {
            result.push_back(tmp);
            t.erase(tmp);
        }
        board[i][j] = '*';
        if(t.existPrefix(tmp)) {
            dfs(board, i, j+1, tmp, result);
            dfs(board, i, j-1, tmp, result);
            dfs(board, i+1, j, tmp, result);
            dfs(board, i-1, j, tmp, result);
        }
        board[i][j] = c;
        tmp.pop_back();
    }
    Trie t;
};

// Solution 2 (100ms)
class TrieNode {
public:
    TrieNode() {
        isKey = false;
        for(int i = 0; i < 26; i++) next[i] = NULL;
    }
    bool isKey;
    TrieNode* next[26];
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        insert(root, word, 0);
    }

    bool search(const string& word) {
        TrieNode * node = search(root, word, 0);
        return node != NULL && node->isKey;
    }

    // Returns if there is any word in the trie that starts with the given prefix.
    bool containsPrefix(const string& prefix) {
        TrieNode* node = search(root, prefix, 0);
        return node != NULL;
    }

private:
    void insert(TrieNode* x, const string& word, int d) {
        if(d == word.size()) { x->isKey = true; return; }
        //if link not exist, create it before descending
        int idx = word[d] - 'a';
        if(x->next[idx] == NULL) x->next[idx] = new TrieNode;
        insert(x->next[idx], word, d+1);
    }
    TrieNode* search(TrieNode* x, const string& word, int d) {
        if(d == word.size()) return x;
        int idx = word[d] - 'a';
        //if link is null, return null;
        if(x->next[idx] == NULL) return NULL;
        return search(x->next[idx], word, d+1);
    }
    TrieNode* root;
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        if(board.empty() || board[0].empty() || words.empty()) return result;
        for(auto w : words) t.insert(w);
        string tmp;
        int m = board.size(), n = board[0].size();
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                dfs(board, i, j, tmp, result);
            }
        }
        return result;
    }
    void dfs(vector<vector<char>>& board, int i, int j, string& tmp, vector<string>& result) {
        int m = board.size(), n = board[0].size();
        tmp += board[i][j];
        char c = board[i][j];
        board[i][j] = '*'; //mark as visited
        if(t.search(tmp)) { //found a word
            int k = 0, size = result.size(); //avoid duplicates
            for(; k < size; k++) if(result[k] == tmp) break;
            if(k == size) result.push_back(tmp); 
        }
        if(t.containsPrefix(tmp)) {
            if(i < m-1 && board[i+1][j] != '*') dfs(board, i+1, j, tmp, result);
            if(j < n-1 && board[i][j+1] != '*') dfs(board, i, j+1, tmp, result);
            if(i > 0 && board[i-1][j] != '*') dfs(board, i-1, j, tmp, result);
            if(j > 0 && board[i][j-1] != '*') dfs(board, i, j-1, tmp, result);
        }
        board[i][j] = c; //reset back to original
        tmp.pop_back();
    }
    Trie t;
};

