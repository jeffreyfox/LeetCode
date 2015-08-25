/*
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?
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

// Morris traversal O(n) without using a stack or recursive calls

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;

        TreeNode *curr = root;
        while(curr) {
            if (!curr->left) {  //no left subtree, visit node and go to right subtree
                ret.push_back(curr->val);
                curr = curr->right;
            } else {
                TreeNode *prev = curr->left; //find curr's predecessor in the tree
                while(prev->right != NULL && prev->right != curr)
                    prev = prev->right;

                if(prev->right == NULL) { //first time, modify pointer
                     prev->right = curr;
                     ret.push_back(curr->val); //visit node first (preorder)
                     curr = curr->left; //go to left subtree
                } else { //second time, revert pointer back to NULL
                     prev->right = NULL;
                     curr = curr->right; //go to right subtree
                }
            }
        }
        return ret;
    }
};
