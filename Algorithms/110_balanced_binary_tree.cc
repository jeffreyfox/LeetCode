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

// Use a recursive function to return whether the tree is balanced, and at the same time set the height of the tree to a reference variable

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        int h = 0;
        return isBalanced(root, h);
    }

    bool isBalanced(TreeNode* root, int& h) {
        if(!root) { h = 0; return true; }
        int hl = 0, hr = 0;
        if(!isBalanced(root->left, hl) || !isBalanced(root->right, hr) || abs(hl-hr) > 1) return false;
        h = max(hl, hr) + 1;
        return true;
    }
};

// Solution 2. One recursive function calculating tree depth and balanced information at the same time! No reference passing needed!
// Use a trick, the height returned has two meanings:
// If 0, means tree is not balanced
// If > 0, means the height of tree + 1. So empty node will return 1.

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return depth(root);
    }
    int depth(TreeNode* root) {
        if(!root) return 1;
        int hl = depth(root->left);
        int hr = depth(root->right);
        if(hl == 0 || hr == 0 || abs(hl - hr) > 1) return 0;
        return max(hl, hr)+1;
    }
};


