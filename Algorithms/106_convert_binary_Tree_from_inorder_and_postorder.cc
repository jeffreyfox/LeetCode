/*
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree. 
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

// Similar idea as 105

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.empty()) return NULL;
        int n = inorder.size();
        return build(inorder, postorder, 0, 0, n);
    }
    //starting positions of arrays and lengths
    TreeNode *build(vector<int>& inorder, vector<int>& postorder, int lo1, int lo2, int len) {
        if(len == 0) return NULL;
        int r = postorder[lo2+len-1];
        TreeNode *root = new TreeNode(r);
        int mid = 0; //number of nodes in left subtree
        while(inorder[lo1+mid] != r) mid++;
        root->left = build(inorder, postorder, lo1, lo2, mid);
        root->right = build(inorder, postorder, lo1+mid+1, lo2+mid, len-mid-1);
        return root;
    }
};
