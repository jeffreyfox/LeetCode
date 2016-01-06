/*
Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
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

// Caveats: 
// 1. empty root should return false.
// 2. leaf node mean node with NO children
// Several cases:
// 1. If reaching an leaf node, check if it's value is equal to sum
// 2. If an internal node, then check left or right subtree
// 3. if root is empty return false

class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        if(!root->left && !root->right) return (sum == root->val);
        sum -= root->val;
        return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
    }
};

//Solution 2.
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        return dfs(root, sum);
    }
    bool dfs(TreeNode* root, int sum) {
        int x = root->val;
        //reaching leaf
        if(!root->left && !root->right && sum == x) return true;
        if(root->left && dfs(root->left, sum-x)) return true;
        if(root->right && dfs(root->right, sum-x)) return true;
        return false;
    }
};

