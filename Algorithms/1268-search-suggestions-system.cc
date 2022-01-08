/*
You are given an array of strings products and a string searchWord.

Design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.

Return a list of lists of the suggested products after each character of searchWord is typed.

 

Example 1:

Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
Output: [
["mobile","moneypot","monitor"],
["mobile","moneypot","monitor"],
["mouse","mousepad"],
["mouse","mousepad"],
["mouse","mousepad"]
]
Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"]
After typing m and mo all products match and we show user ["mobile","moneypot","monitor"]
After typing mou, mous and mouse the system suggests ["mouse","mousepad"]
Example 2:

Input: products = ["havana"], searchWord = "havana"
Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
Example 3:

Input: products = ["bags","baggage","banner","box","cloths"], searchWord = "bags"
Output: [["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]
 

Constraints:

1 <= products.length <= 1000
1 <= products[i].length <= 3000
1 <= sum(products[i].length) <= 2 * 104
All the strings of products are unique.
products[i] consists of lowercase English letters.
1 <= searchWord.length <= 1000
searchWord consists of lowercase English letters.
*/

// Use a Trie. Caveats:
// 1. When inserting to the trie, first check if the child node is not nullptr before creating a new child node.
// 2. When searching in the trie, first check if the child node is nullptr. If yes, return false immediately instead of dereferencing the node pointer.

class Trie {
public:
    struct Node {
        bool isLeaf;
        vector<Node*> children;
        Node() : isLeaf(false), children(vector<Node*>(26, nullptr)) {}        
    };
    
    Trie() {
        root = new Node();
    }    
    
    void insert(const string &word) {
        Node* node = root;
        for (auto c : word) {
            if (node->children[c-'a'] == nullptr) {
                node->children[c-'a'] = new Node();
            }
            node = node->children[c-'a'];
        }
        node->isLeaf = true;
    }
    
    vector<string> search(const string &prefix) {
        Node* node = root;
        for (auto c : prefix) {
            if (node->children[c-'a'] == nullptr) return {};
            node = node->children[c-'a'];
        }
        vector<string> result;
        string tmp = prefix;
        dfs(node, tmp, result);
        return result;
    }

private:
    // find at most 3 strings under node
    void dfs(Node* node, string& tmp, vector<string>& result) {
        if (result.size() == 3 || node == nullptr) return;
        if (node->isLeaf) {
            result.push_back(tmp);
            if (result.size() == 3) return;
        }
        for (int i = 0; i < 26; ++i) {
            tmp.push_back('a' + i);
            dfs(node->children[i], tmp, result);
            if (result.size() == 3) return;
            tmp.pop_back();
        }
    }
    Node *root;
};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Trie trie;
        for (const auto &p : products) {
            trie.insert(p);
        }
        
        vector<vector<string>> result;
        for (int i = 1; i <= searchWord.size(); ++i) {
            const string prefix = searchWord.substr(0, i);
            result.push_back(trie.search(prefix));
        }
        return result;
    }
};
