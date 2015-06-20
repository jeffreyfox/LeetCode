/// C++ version, use recursion.

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
