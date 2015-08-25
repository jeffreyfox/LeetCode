/*
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution? 

*/
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// First do inorder traversal. Then find abnormal elements. Two cases:
// 1   3   2   4   5
//      3>2: n1 = 3, n2 = 2;
// 1   4   3   2   5
//      4>3 3>2: n1 = 4, n2 = 2;
//swap values of two nodes, not nodes themselves

class Solution {
public:
   void recoverTree(TreeNode* root) {
        if(!root) return;
        vector<TreeNode*> nodes;
        inorder(root, nodes);
        TreeNode *n1(NULL), *n2(NULL);
        for (size_t i = 0; i < nodes.size()-1; ++i) {
            if(nodes[i]->val > nodes[i+1]->val) {
                if(!n1) n1 = nodes[i];
                n2 = nodes[i+1];
            }
        }
        if(n1 && n2) {
            int tmp = n1->val;
            n1->val = n2->val;
            n2->val = tmp;
        }
    }
    void inorder(TreeNode *root, vector<TreeNode*>& nodes) {
       if(!root) return;
       inorder(root->left, nodes);
       nodes.push_back(root);
       inorder(root->right, nodes);
    }
};
