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

// Solution 2, slightly different.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.empty()) return NULL;
        int n = inorder.size();
        return buildTree(inorder, 0, n-1, postorder, 0, n-1);
    }
    //build tree from in[i1 .. i2] and post[p1 .. p2]
    TreeNode* buildTree(vector<int>& inorder, int i1, int i2, vector<int>& postorder, int p1, int p2) {
        int len = p2 - p1 + 1;
        if(len <= 0) return NULL;
        if(len == 1) return new TreeNode(postorder[p1]); //one node only
        int root_val = postorder[p2]; //last one is root
        TreeNode *root = new TreeNode(root_val);
        
        int i = i1;
        for(; i <= i2; i++) {
            if(inorder[i] == root_val) break;
        }
        //i is the root in inorder
        int nl = i-i1; //number of elements in left subtree
        root->left = buildTree(inorder, i1, i-1, postorder, p1, p1+nl-1);
        root->right = buildTree(inorder, i+1, i2, postorder, p1+nl, p2-1);
    }
};

