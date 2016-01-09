/*
Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.

Note:

    Given target value is a floating point.
    You are guaranteed to have only one unique value in the BST that is closest to the target.
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

// Iterative solution. Search down the tree.
// Caveat: Do not initialize mind as MAX_INT.
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        double mind = fabs(target - root->val);
        int result = root->val;
        while(root) {
            double diff = fabs(target - root->val);
            if(diff == 0.0) return target;
            if(diff < mind) {
                result = root->val;
                mind = diff;
            }
            if(target > root->val) root = root->right;
            else root = root->left;
        }
        return result;
    }
};

