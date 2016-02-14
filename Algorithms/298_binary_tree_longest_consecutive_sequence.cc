/*
Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).

For example,
   1
    \
     3
    / \
   2   4
        \
         5
Longest consecutive sequence path is 3-4-5, so return 3.
   2
    \
     3
    / 
   2    
  / 
 1
Longest consecutive sequence path is 2-3,not3-2-1, so return 2.
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
 
 // solution using a global variable
 
class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        if(!root) return 0;
        max_len = 1; //at least one
        helper(root);
        return max_len;
    }
    //longest consecutive starting from root
    int helper(TreeNode* root) {
        if(!root) return 0;
        int hl = helper(root->left);
        int hr = helper(root->right);
        int h = 1;
        if(root->left && root->left->val == root->val + 1) h = max(h, hl+1);
        if(root->right && root->right->val == root->val + 1) h = max(h, hr+1);
        max_len = max(max_len, max(h, max(hl, hr)));
        return h;
    }
    int max_len;
};
