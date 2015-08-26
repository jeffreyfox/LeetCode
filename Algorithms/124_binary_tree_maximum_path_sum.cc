/*
Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

For example:
Given the below binary tree,

       1
      / \
     2   3

Return 6. 
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

/// Recursive solution. 
// Maximum path sum of tree rooted at x is the maximum of:
/// 1. maximum path sum of x's left subtree (not passing x)
/// 2. maximum path sum of x's right subtree (not passing x)
/// 3. maximum path crossing x (x->val + maximum path from x's left child to anywhere in x's left subtree + maximum path from x's right child to anywhere in x's right subtree)
/// Note that the node values can be negative, so in case 3, some paths can be length 0.

class Solution {
public:
    int maxPathSum(TreeNode* root) {
       if(!root) return 0;
       int sum_from_root(0);
       return maxPathSum(root, sum_from_root);
    }
    int maxPathSum(TreeNode *root, int& sum_from_root) {
        int msfr_left(INT_MIN), msfr_right(INT_MIN); //from root
        int ms_left(INT_MIN), ms_right(INT_MIN);  //maximum path sum of left and right subtrees
        if(root->left)
            ms_left = maxPathSum(root->left, msfr_left);

        if(root->right)
            ms_right = maxPathSum(root->right, msfr_right);

        //maximum sum of paths starting from root
        sum_from_root = root->val + max(0, max(msfr_left, msfr_right));

        //maximum sum of paths crossing root
        int mps = root->val + max(msfr_left, 0) + max(msfr_right, 0);

        return max(mps, max(ms_left, ms_right));
    }
};
