/*
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than the node's key.
    Both the left and right subtrees must also be binary search trees.

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
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

// Recursive solution.
// store lower and upper bounds of each subtree, initially it is (-inf, inf)
// One corner case is when INT_MIN and INT_MAX is part of the value, so use LONG_MIN and LONG_MAX instead.

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return validate(root, LONG_MIN, LONG_MAX);
    }
    //make sure all tree values between (lo, hi)
    bool validate(TreeNode* root, long lo, long hi) {
        if(!root) return true;
        int x = root->val;
        if(x <= lo || x >= hi) return false;
        return validate(root->left, lo, x) && validate(root->right, x, hi);
    }
};

// 2021. Uses two booleans instead of long bounds
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidHelper(root, 0, 0, false, false);
    }
    
    bool isValidHelper(TreeNode * root, int lo, int hi, bool lo_initialized, bool hi_initialized) {
        if (root == nullptr) return true;
        if (lo_initialized && root->val <= lo) return false;
        if (hi_initialized && root->val >= hi) return false;        
        // Recurse on the children
        return isValidHelper(root->left, lo, root->val, lo_initialized, true) && isValidHelper(root->right, root->val, hi, true, hi_initialized);
    }
};
