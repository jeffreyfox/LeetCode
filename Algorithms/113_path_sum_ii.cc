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

// DFS backtracking. Recursive solution.
// Caveats: when reaching leaf, compare sum with x, not with zero!

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int> > result;
        if(!root) return result;
        vector<int> path;
        dfs(root, sum, path, result);
        return result;
    }
    void dfs(TreeNode* root, int sum, vector<int>& path, vector<vector<int> >& result) {
        int x = root->val;
        path.push_back(x);
        //reaching leaf
        if(!root->left && !root->right && sum == x) result.push_back(path);
        if(root->left) dfs(root->left, sum-x, path, result);
        if(root->right) dfs(root->right, sum-x, path, result);
        path.pop_back();
    }
};
