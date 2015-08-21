/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?
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

// Recursive solution (easy).

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        inorder(root, ret);
        return ret;
    }
    void inorder(TreeNode* root, vector<int>& ret) {
        if(!root) return;
        if(root->left) inorder(root->left, ret);
        ret.push_back(root->val);
        if(root->right) inorder(root->right, ret);
    }
};
