/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return NULL;
        //swap left and right children
        TreeNode *t = root->left;
        root->left = root->right;
        root->right = t;
        //recursively run invert on subtrees
        root->left = invertTree(root->left);
        root->right = invertTree(root->right);
    }
};
