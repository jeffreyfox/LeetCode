/*
Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z. 
*/

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");

/// Solution 1, simpler, with delete function (which slows down runtime by 40 ms!)

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
        isKey = false;
        links.resize(26, NULL);
    }

    bool isKey;
    vector<TrieNode*> links;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        eraseUtil(root);
    }
    // Inserts a word into the trie.
    void insert(string word) {
        insertUtil(root, word, 0);
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode* node = searchUtil(root, word, 0);
        return node != NULL && node->isKey;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* node = searchUtil(root, prefix, 0);
        return node != NULL;
    }

private:
    //root can never be NULL
    void insertUtil(TrieNode* root, const string& word, int i) {
        if(i == word.size()) { root->isKey = true; return; }
        int c = word[i] - 'a';
        if(!root->links[c]) root->links[c] = new TrieNode();
        insertUtil(root->links[c], word, i+1);
    }
    TrieNode* searchUtil(TrieNode* root, const string& word, int i) {
        if(root == NULL) return NULL;
        if(i == word.size()) return root;
        int c = word[i] - 'a';
        return searchUtil(root->links[c], word, i+1);
    }
    void eraseUtil(TrieNode* root) {
        if(!root) return;
        for(int c = 0; c < 26; ++c) eraseUtil(root->links[c]);
        delete root;
    }
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");


/// Solution 2, slightly different.

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
        links = new TrieNode*[26];
        for (int i = 0; i < 26; ++i)
            links[i] = NULL;
        isKey = false;
    }
    
    TrieNode** links; //array of pointers
    bool isKey;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        root = insert(root, word, 0);
    }

    TrieNode* insert(TrieNode* x, string word, int d) {
        if (x == NULL) { x = new TrieNode(); }
        if (d == word.size()) x->isKey = true;
        else {
            int i = word[d] - 'a';
            x->links[i] = insert(x->links[i], word, d+1);
        }
        return x;
    }
    
    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode *x = search(root, word, 0);
        return (x != NULL && x->isKey);
    }
    
    TrieNode* search(TrieNode* x, string word, int d) {
        if (x == NULL) return NULL;
        if (d == word.length()) return x;
        int i = word[d] -'a';
        return search(x->links[i], word, d+1);
    }
    
    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* x = search(root, prefix, 0);
        return x != NULL;
    }
    
private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
