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

// Solution 2, slightly different version

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()) return NULL;
        int n = preorder.size();
        return buildTree(preorder, 0, n-1, inorder, 0, n-1);
    }
    //build tree from pre[p1 ..p2] and in[i1 .. i2]
    TreeNode* buildTree(vector<int>& preorder, int p1, int p2, vector<int>& inorder, int i1, int i2) {
        int len = p2 - p1 + 1;
        if(len <= 0) return NULL;
        if(len == 1) return new TreeNode(preorder[p1]); //one node only
        int root_val = preorder[p1];
        TreeNode *root = new TreeNode(root_val);
        
        int i = i1;
        for(; i <= i2; i++) {
            if(inorder[i] == root_val) break;
        }
        //i is the root in inorder
        int nl = i-i1; //number of elements in left subtree
        root->left = buildTree(preorder, p1+1, p1+nl, inorder, i1, i-1);
        root->right = buildTree(preorder, p1+nl+1, p2, inorder, i+1, i2);
    }
};
