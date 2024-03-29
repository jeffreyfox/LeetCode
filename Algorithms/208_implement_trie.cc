/*
Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z. 
*/

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");

// 2021.
// Caveats: When inserting, only creates new nodes when the link doesn't exist!
class Trie {
public:   
    struct TriNode {
        bool isKey;
        std::vector<TriNode*> next;
        TriNode() : isKey(false) {
            next.resize(26, nullptr);
        }
    };

    Trie() {
        root = new TriNode;
    }
    
    void insert(string word) {
        TriNode *curr = root;
        for (const auto c : word) {
            int idx = c-'a';
            if (!curr->next[idx]) curr->next[idx] = new TriNode;
            curr = curr->next[idx];  
        }
        curr->isKey = true;
    }
    
    bool search(string word) {
        TriNode *curr = root;
        for (const auto c : word) {
            if (!curr->next[c - 'a']) return false;
            curr = curr->next[c - 'a'];
        }
        return curr->isKey;
    }
    
    bool startsWith(string prefix) {
        TriNode *curr = root;
        for (const auto c : prefix) {
            if (!curr->next[c - 'a']) return false;
            curr = curr->next[c - 'a'];
        }
        return true;
    }
private:
    TriNode *root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

// 2015.
/// Solution 1. Follows the Java implementation from the Sedgewick book.
/// The character we are currently at does not correpsond to the node itself, but one of its links!

/// When we do search(x, str, d), we are actually looking for x->next[str[d]] !, 
/// e.g. ab , when d == 0, we search character 'a' in the first link of root.
/// Then we search b in the second link of node 'a'. When we arrive b, we have d == 2, pointing to str.end(). then we check if b is a key.
/// When d reaches one past the end of str, return the node we are currently at.
/// If we encountered a NULL node before that, we simply return null.

/// When we do insert(x, str, d), we are actually inserting str[d] to the associated next link of the node x.
/// e.g. inserting ab to empty trie. first insert(root, "ab", 0), which directly goes to root->next[0], and we have 
/// insert(root->next[0], "ab", 1), we first need to create the node corresponding to 'a' (this node is pointed by the first link of root)
/// in the last step, so it is interpreted as 'a'. Then we should check its second link for 'b'. We then call
/// insert(a_node->next[1], "ab", 2), we again need to create one, then as d reaches the end, we set isKey to true, and then return the node (not its links)
/// When not reaching the end, we need to recursively call the insert of its links, and return the new link address. We finally return the node x.

class TrieNode {
public:
    // Initialize your data structure here.
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

    // Inserts a word into the trie.
    void insert(string word) {
        root = insert(root, word, 0);
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode * node = search(root, word, 0);
        return node != NULL && node->isKey;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* node = search(root, prefix, 0);
        return node != NULL;
    }

private:
    TrieNode* insert(TrieNode* x, const string& word, int d) {
        if(x == NULL) x = new TrieNode;
        if(d == word.size()) { x->isKey = true; return x; }
        int idx = word[d] - 'a';
        x->next[idx] = insert(x->next[idx], word, d+1);
        return x;
    }
    TrieNode* search(TrieNode* x, const string& word, int d) {
        if(x == NULL) return NULL;
        if(d == word.size()) return x;
        int idx = word[d] - 'a';
        return search(x->next[idx], word, d+1);
    }
    TrieNode* root;
};

/// Solution 2. Slightly simpler, make sure search and insert will never encounter null nodes, can remove the check of x == NULL.
/// this also reduces stack depth by one (no need to descend in to a null node), and easier to comprehend.

class TrieNode {
public:
    // Initialize your data structure here.
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

    // Inserts a word into the trie.
    void insert(string word) {
        insert(root, word, 0);
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode * node = search(root, word, 0);
        return node != NULL && node->isKey;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
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

/// Solution 3, with delete function (which slows down runtime by 40 ms!)

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

