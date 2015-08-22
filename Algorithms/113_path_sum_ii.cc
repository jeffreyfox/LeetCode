/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1

return

[
   [5,4,11,2],
   [5,8,4,5]
]
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

// DFS backtracking.

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int> > ret;
        if(!root) return ret;
        vector<int> path;
        pathSum(root, sum, path, ret);
        return ret;
    }
    void pathSum(TreeNode *root, int sum, vector<int>& path, vector<vector<int> >& ret) {
        if(root == NULL) return;
        
        path.push_back(root->val);
        
        if(!root->left && !root->right && sum == root->val) {
            ret.push_back(path); //add to solution
        } else {
            pathSum(root->left, sum-root->val, path, ret); //left subtree
            pathSum(root->right, sum-root->val, path, ret); //right subtree
        }
        path.pop_back(); //back track
    }
};
