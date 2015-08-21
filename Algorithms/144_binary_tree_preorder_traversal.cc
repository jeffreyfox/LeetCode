/*
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,2,3].

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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        preorder(root, ret);
        return ret;
    }
    void preorder(TreeNode *root, vector<int>& ret) {
        if(!root) return;
        ret.push_back(root->val);
        preorder(root->left, ret);
        preorder(root->right, ret);
    }
};
