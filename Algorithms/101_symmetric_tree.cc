/*
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3

But the following is not:

    1
   / \
  2   2
   \   \
   3    3
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

// Recursive solution. check if the left and right subtrees are symmetric or not
// Two non-empty trees are symmetric iff:
// 1. root1 = root2 &&
// 2. 1's left is symmetric to 2's right &&
// 3. 2's left is symmetric to 1's right

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == NULL) return true;
        return isSymmetric(root->left, root->right);
    }
    
    bool isSymmetric(TreeNode* left, TreeNode *right) {
        if(left == NULL) return right == NULL;
        if(right == NULL) return false;
        if(left->val != right->val) return false;
        return isSymmetric(left->left, right->right) && isSymmetric(left->right, right->left);
    }
};

