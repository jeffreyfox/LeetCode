/*
 Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6

The flattened tree should look like:

   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6

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

// Recursive solution. First flatten right, then left, then insert left list between root and root->right. Finally, remember to set root->left to NULL!
// Caveat: Set root->left to NULL in the end!

class Solution {
public:
    void flatten(TreeNode* root) {
        if(!root) return;
        flatten(root->right);
        flatten(root->left);
        if(root->left) {
            TreeNode *node = rightMostChild(root->left);
            node->right = root->right;
            root->right = root->left;
        }
        root->left = NULL;
    }
    
    TreeNode *rightMostChild(TreeNode* root) {
        while(root->right) root = root->right;
        return root;
    }
};
