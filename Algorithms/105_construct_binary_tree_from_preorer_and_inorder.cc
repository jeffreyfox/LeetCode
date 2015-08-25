/*
Given preorder and inorder traversal of a tree, construct the binary tree.

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

// Recursive solution. Use start and length of subarray as parameter
/// pre: [  X  [ left ] [ right ] ] : total length = len
///        lo1    mid    len-mid+1
/// in:  [ [ left ]  X  [ right ] ] : total length = len
///        lo2  mid      len-mid+1
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()) return NULL;
        int n = preorder.size();
        return build(preorder, inorder, 0, 0, n);
    }
    //starting positions of arrays and lengths
    TreeNode *build(vector<int>& preorder, vector<int>& inorder, int lo1, int lo2, int len) {
        if(len == 0) return NULL;
        int r = preorder[lo1];
        TreeNode *root = new TreeNode(r);
        int mid = 0; //number of nodes in left subtree
        while(inorder[lo2+mid] != r) mid++;
        root->left = build(preorder, inorder, lo1+1, lo2, mid);
        root->right = build(preorder, inorder, lo1+1+mid, lo2+mid+1, len-mid-1);
        return root;
    }
};
