/// Use a Trie data-structure.
/// Perform dfs on the board, construct the string formed by the path, see if it is contained as prefix in the Trie, if not, then stop searching/// this is the essense of using Trie to speed up search.
/// One caveat is that you need to avoid duplicated entries in the return array, so a found() function is needed

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
    //whether trie contains a key with prefix of "word"?
    bool containsPrefix(const string& word) const {
        Node* node = get(root, word, 0);
        return node != NULL;
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

    Node* root; //root of trie
};

class Solution {
public:
    vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
        vector<string> ret;
        
        Trie dict; //dictionary
        for (size_t i = 0; i < words.size(); ++i) //insert words to dictionary
            dict.put(words[i]);
        
        int m = board.size();
        int n = board[0].size();
        vector<vector<bool> > marked(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                findWords(board, i, j, dict, string(""), marked, ret); //insert word to ret if found in dictionary
            }
        }
        return ret;
    }

    //see whether key pref + board[i][j] is in dictionary
    void findWords(vector<vector<char> >& board, int i, int j, const Trie& dict, string pref, vector<vector<bool> >& marked, vector<string>& ret) {
        if (!isValidPos(board, i, j, marked)) return; //not valid position
        pref = pref + board[i][j];
        
        if (!dict.containsPrefix(pref)) return; // if no prefix found, return (essential for fast search)
        if (dict.contains(pref) && !found(ret, pref)) ret.push_back(pref); //add to solution if found key, avoid duplicates
        
        marked[i][j] = true; //mark as visited
        findWords(board, i+1, j, dict, pref, marked, ret);
        findWords(board, i-1, j, dict, pref, marked, ret);
        findWords(board, i, j+1, dict, pref, marked, ret);
        findWords(board, i, j-1, dict, pref, marked, ret);
        marked[i][j] = false;
    }
    //whether (i, j) is a valid position (not outside domain, and is not visited before)
    bool isValidPos(vector<vector<char> >& board, int i, int j, vector<vector<bool> >& marked) {
        int m = board.size();
        int n = board[0].size();
        return (i >= 0 && i < m && j >= 0 && j < n) && !marked[i][j];
    }
    // check if word is found in the words array
    bool found(const vector<string>& words, const string& word) {
        for (size_t i = 0; i < words.size(); ++i)
            if (words[i] == word) return true;
        return false;
    }
};
