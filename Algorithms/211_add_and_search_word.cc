/*
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

For example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.
*/

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");

/// Use a trie as underlying data-structure, search function now returns boolean, and supports checking wildcard '.'
/// if new character is normal a-z, do normal search, otherwise it is a '.', then check all non-null next links

class TrieNode {
public:
    TrieNode() : isKey(false) {
        for(int i = 0; i < 26; i++) next[i] = NULL;
    }
    bool isKey;
    TrieNode* next[26];
};

class Trie {
public:
    Trie() { root = new TrieNode; }
    
    void insert(const string& word) {
        insert(root, word, 0);
    }
    bool search(const string& word) {
        return search(root, word, 0);
    }
    
private:
    void insert(TrieNode *x, const string& word, int d) {
        if(d == word.size()) { x->isKey = true; return; }
        int idx = word[d] - 'a';
        if(x->next[idx] == NULL) x->next[idx] = new TrieNode;
        insert(x->next[idx], word, d+1);
    }
    //x will never be null
    bool search(TrieNode *x, const string& word, int d) {
        if(d == word.size()) return x->isKey;
        if(word[d] != '.') {
            int idx = word[d] - 'a';
            return (x->next[idx] && search(x->next[idx], word, d+1));
        } else {
            for(int idx = 0; idx < 26; idx++) {
                if(x->next[idx] && search(x->next[idx], word, d+1)) return true;
            }
            return false;
        }
    }
    TrieNode* root;
};

class WordDictionary {
public:
    WordDictionary() : t() {}
    // Adds a word into the data structure.
    void addWord(string word) {
        t.insert(word);
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return t.search(word);
    }
    Trie t;
};
