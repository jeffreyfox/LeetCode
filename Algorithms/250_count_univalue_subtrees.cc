/*
Given a binary tree, count the number of uni-value subtrees.

A Uni-value subtree means all nodes of the subtree have the same value.

For example:
Given binary tree,

              5
             / \
            1   5
           / \   \
          5   5   5

return 4. 
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

// Recursive solution. Use a helper function to count the univalue subtrees and also return whether the tree itself is univalue.
// An empty tree is defined to be univalue.
// A tree is univalue iff:
// 1. left and right tree are both univalue
// 2. if left/right child is not empty, the node value of left/right child should be equal to root value.

class Solution {
public:
    int countUnivalSubtrees(TreeNode* root) {
        int count = 0;
        helper(root, count);
        return count;
    }
    bool helper(TreeNode* root, int& count) {
        if(!root) { count = 0; return true; }
        int cl(0), cr(0);
        TreeNode *l = root->left, *r = root->right;
        bool uniVal_l = helper(l, cl);
        bool uniVal_r = helper(r, cr);
        count = cl + cr;
        if((uniVal_l && (!l || l->val == root->val)) && (uniVal_r && (!r || r->val == root->val))) {
            count += 1;
            return true; //root is univalue tree
        } else return false; //root is not univalue tree
    }
};

