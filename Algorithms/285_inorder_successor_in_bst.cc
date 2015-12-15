/*
Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null. 
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

/*
Several cases:
1. If p has right subtree, then just return the minimum in right subtree.
2. Otherwise, need to go to its ancestors. First build a search path from root to p, then search backwards, if found a path going toward left, then the higher one is the successor.
3. If not found such path, that means p is lying at bottom right of tree, and there is no successor. Return NULL.
Caveats:
tree is BST! So don't use backtracking to seach for path, use O(logn) iterative approach utilizing BST properly!

*/

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root || !p) return NULL;
        if(p->right) return findMin(p->right);
        //need to find path from root to p
        vector<TreeNode*> path;
        bool found = findPath(root, p, path);
        if(!found) return NULL;
        int n = path.size(), i = 0;
        for(i = n-1; i > 0; i--) {
            //is left subtree
            if(path[i-1]->left == path[i]) return path[i-1];
        }
        return NULL;
    }
    bool findPath(TreeNode* root, TreeNode* p, vector<TreeNode*>& path) {
        while(root) {
            path.push_back(root);
            if(root == p) return true;
            else if(p->val < root->val) root = root->left;
            else root = root->right;
        }
        return false;
    }
    TreeNode* findMin(TreeNode* root) {
        while(root->left) root = root->left;
        return root;
    }
};

//Alternative solution using a stack
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root || !p) return NULL;
        if(p->right) return findMin(p->right);
        //need to find path from root to p
        stack<TreeNode*> path;
        bool found = findPath(root, p, path);
        if(!found) return NULL;
        while(!path.empty()) {
            TreeNode *ancestor = path.top(); 
            path.pop(); 
            //is left subtree
            if(!path.empty() && path.top()->left == ancestor) return path.top();
        }
        return NULL;
    }
    bool findPath(TreeNode* root, TreeNode* p, stack<TreeNode*>& path) {
        while(root) {
            path.push(root);
            if(root == p) return true;
            else if(p->val < root->val) root = root->left;
            else root = root->right;
        }
        return false;
    }
    TreeNode* findMin(TreeNode* root) {
        while(root->left) root = root->left;
        return root;
    }
};


