/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

// Solution 1. Use leetcode format, null represented by "#". Do level-order traversal. For the last layer, ignore all "#"s (using hasNode variable)

class Codec {
public:
    //format: length 1 2 # ...
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return "";
        string str;
        string tmp;
        bool hasNodes = false;
        vector<TreeNode*> curr, next; //BFS, two levels
        curr.push_back(root);
        while(!curr.empty()) {
            tmp = "";
            hasNodes = false;
            for(auto node : curr) {
                if(node) {
                    hasNodes = true;
                    next.push_back(node->left);
                    next.push_back(node->right);
                }
                if(tmp != "") tmp += " ";
                tmp += node ? to_string(node->val) : "#";
            }
            if(hasNodes) str += (str == "") ? tmp : " " + tmp;
            swap(curr, next);
            next.clear();
        }
        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == "") return NULL;
        vector<TreeNode*> curr, next; //BFS, two levels
        int i = 0, n = data.size();
        string num = getNum(data, i);
        TreeNode *root = new TreeNode(atoi(num.c_str()));
        curr.push_back(root);
        while(i < n) {
            for(auto node : curr) {
                string l = getNum(data, i);
                string r = getNum(data, i);
                if(l != "#") {
                    node->left = new TreeNode(atoi(l.c_str()));
                    next.push_back(node->left);
                }
                if(r != "#") {
                    node->right = new TreeNode(atoi(r.c_str()));
                    next.push_back(node->right);
                }
            }
            swap(curr, next);
            next.clear();
        }
        return root;
    }

    string getNum(const string& s, int& i) {
        int n = s.size();
        int j = i;
        while(i < n && s[i] != ' ') i++;
        int len = i-j;
        i++; //move one step further
        return s.substr(j, len);
    }
};

// Solution 2. Recursive solution. Use brackets [root, left-subtree, right-subtree], so above tree will look like:
// [1 [ 2 [] [] ] [ 3 [4[][]] [5[][]] ] ]
// when deserializing, need to find the matching ']' to the first '['

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return "[]";
        else return "[" + to_string(root->val) + serialize(root->left) + serialize(root->right) + "]";
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        return deserializeUtil(data, 0, data.size()-1);
    }
    TreeNode* deserializeUtil(const string& data, int lo, int hi) {
        int len = hi-lo+1;
        if(len <= 2) return NULL;
        lo++; hi--; //remove the bounding "[]"
        int i = lo;
        while(i <= hi && data[i] != '[') i++; //i->'['
        int val = atoi(data.substr(lo, i-lo).c_str());
        TreeNode* root = new TreeNode(val);
        //find the matching ']'
        int j = i+1;
        int diff = 1; //# left - # right
        while(j <= hi) {
            if(data[j] == '[') diff++;
            else if(data[j] == ']') {
                diff--;
                if(diff == 0) break; //found matching ']'
            }
            j++;
        }
        root->left = deserializeUtil(data, i, j); //i->'[', j -> ']'
        root->right = deserializeUtil(data, j+1, hi);
        return root;
    }
};

