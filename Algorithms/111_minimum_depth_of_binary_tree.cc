/*
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
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

// Caveat: This is different from the maxDepth problem!. There are several cases:
// 1. single node (no left or right children): minD = 1;
// 2. only left child: minD = 1 + minD of left
// 3. only right child: minD = 1 + minD of right
// 4. both childs: mindepth = 1 + min(minD of left, minD of right)

class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        int minD = 0;
        if(!root->left)  minD = minDepth(root->right);
        else if(!root->right) minD = minDepth(root->left);
        else minD = min(minDepth(root->left), minDepth(root->right));
        return minD+1;
    }
};
