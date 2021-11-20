/*
The thief has found himself a new place for his thievery again. There is only one entrance to this area, called root.

Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that all houses in this place form a binary tree. It will automatically contact the police if two directly-linked houses were broken into on the same night.

Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.

 

Example 1:


Input: root = [3,2,3,null,3,null,1]
Output: 7
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:


Input: root = [3,4,5,1,3,null,1]
Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
0 <= Node.val <= 104
*/

// Recursive solution. Returning two numbers which are maximum profit when robbing and not robbing tree at root.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int rob(TreeNode* root) {
        auto result = robHelper(root);
        return max(result[0], result[1]);
    }
    // vector storing two numbers:
    // [0]: max value if robbing root
    // [1]: max value if not robbing root
    vector<int> robHelper(TreeNode *root) {
        if (!root) return {0, 0}; 
        
        vector<int> result(2);
        auto left = robHelper(root->left);
        auto right = robHelper(root->right);      
        result[0] = root->val + left[1] + right[1];
        result[1] = max(left[0], left[1]) + max(right[0], right[1]);
        return result;
    }
};
