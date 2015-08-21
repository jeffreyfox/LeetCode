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

// Iterative solution using a stack

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        deque<TreeNode*> s; //stack
        s.push_back(root);
        while(!s.empty()) {
            TreeNode *node = s.back(); s.pop_back();
            ret.push_back(node->val);
            if(node->right) s.push_back(node->right);
            if(node->left) s.push_back(node->left);
        }
        return ret;
    }
};
