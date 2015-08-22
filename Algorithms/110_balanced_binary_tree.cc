/*
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1. 
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

// Recursive solution. A tree is balanced iff:
// 1. left and right subtree are both balanced
// 2. depth of left and right subtree differ by at most 1

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if (!root) return true;
        return ( isBalanced(root->left) && isBalanced(root->right) && abs(maxDepth(root->left) - maxDepth(root->right)) <= 1 );
    }
    
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

