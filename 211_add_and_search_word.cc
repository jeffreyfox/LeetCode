/// Use a trie as underlying data-structure
/// Implement pattern search functionality (support wildcard '.')

class Trie {
public:
    struct Node {
        bool isKey;
        Node** links; // array of nodes
        Node() : isKey(false) {
            links = new Node*[26];
            for (int i = 0; i < 26; ++i)
                links[i] = NULL;
        }
    };
    
    Trie() { root = new Node(); }

    //whether trie contains a key that equals "word"?
    bool contains(const string& word) const {
        Node* node = get(root, word, 0);
        return node != NULL && node->isKey;
    }
    
    //whether trie contains a key that equals "word"? (key can have '.')
    bool containsPattern(const string& word) const {
        return containsPattern(root, word, 0);
    }  

    void put(const string& word) {
        root = put(root, word, 0);
    }

private:

    Node* get(Node* node, const string& word, int k) const {
        if (node == NULL) return NULL;
        if (k == word.size()) return node;
        int i = word[k] - 'a';
        return get(node->links[i], word, k+1);
    }
    
    Node* put(Node*& node, const string& word, int k) {
        if (node == NULL) node = new Node();
        if (k == word.size()) node->isKey = true;
        else {
            int i = word[k] - 'a';
            node->links[i] = put(node->links[i], word, k+1);
        }
        return node;
    }
    bool containsPattern(Node* node, const string& word, int k) const {
        if (node == NULL) return false;
        if (k == word.size()) return node->isKey;
        if (word[k] != '.') {
            int i = word[k] - 'a';
            return containsPattern(node->links[i], word, k+1);
        } else { // char is a wildcard '.'
            for (int i = 0; i < 26; ++i)
                if (containsPattern(node->links[i], word, k+1)) return true;
            return false;
        }
    }
    Node* root; //root of trie
};

class WordDictionary {
public:

    // Adds a word into the data structure.
    void addWord(string word) {
        dict.put(word);
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return dict.containsPattern(word);
    }
    
private:
    Trie dict; //dictionary
};

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");
