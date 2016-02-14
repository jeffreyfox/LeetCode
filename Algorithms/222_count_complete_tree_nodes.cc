/*
Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
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
 
// solution using a function to get the height of left spine of tree. time complexity is:
// lgn + ... + 1 = lgn lgn

class Solution {
public:
    int countNodes(TreeNode* root) {
        if(!root) return 0;
        int h = leftSpineHeight(root);
        int count = (1 << h) - 1; // total possible nodes for tree at root: 2^h-1
        while(root) { //subtree under root may not be full
            h--;
            int hr = leftSpineHeight(root->right);
            if(hr < h) {
                count -= (1 << hr); // exclude missing nodes: 2^hr
                root = root->left;
            } else {
                root = root->right;
            }
        }
        return count;
    }

    int leftSpineHeight(TreeNode* root) {
        int h = 0;
        while(root) {
            root = root->left;
            h++;
        }
        return h;
    }
};
