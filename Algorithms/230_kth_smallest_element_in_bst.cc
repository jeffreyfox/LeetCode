/*
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Hint:

    Try to utilize the property of a BST.
    What if you could modify the BST node's structure?
    The optimal runtime complexity is O(height of BST).
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

//First find minimum, and store the search path. Then do inorder traversal k times.
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        if(!root) return 0;
        stack<TreeNode*> path;
        while(root) {
            path.push(root);
            root = root->left;
        }
        TreeNode* node(NULL);
        int i = 1;
        while(1) {
            if(path.empty()) return 0;
            node = path.top(); path.pop();
            if(i == k) return node->val;
            i++;
            node = node->right;
            while(node) {
                path.push(node); node = node->left;
            }
        }
        return 0;
    }
};

