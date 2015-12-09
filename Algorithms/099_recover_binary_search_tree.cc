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

/*
Solution 1. Using morris traversal. Morris traversal (alternative while loop where visit only appears once)

When finding swapped elements, can optimize and use :

if(!n1) n1 = prev;
n2 = node;

 1   3   2   4   5
      3>2: n1 = 3, n2 = 2;
 1   4   3   2   5
      4>3 3>2: n1 = 4, n2 = 2;
swap values of two nodes, not nodes themselves

*/

class Solution {
public:
   void recoverTree(TreeNode* root) {
        if(!root) return;
        TreeNode *node = root, *prev = NULL;
        TreeNode *n1(NULL), *n2(NULL); //node to be swapped
        //now starts morris traversal
        while(node) {
            if(node->left) {  // has left subtree
                TreeNode *child = node->left;
                while(child->right != NULL && child->right != node) child = child->right;
                //reached right most child of left subtree
                if(child->right == NULL) { //first time
                    child->right = node;
                    node = node->left;
                    continue;
                } else { //second time
                   child->right = NULL; //second time
                }
            }
            //visit node, then move to right
            if(prev && prev->val > node->val) {
                if(!n1) n1 = prev;
                n2 = node;
            }
            prev = node;
            node = node->right;
        }
        if(n1 && n2) {
            int t = n1->val;
            n1->val = n2->val;
            n2->val = t;
        }
   }
};

/*
Another solution using inorder traversal without vector<>. Just store prev at last step and compare with node->val at current step.
O(lg n) space for the stack space of recursive calls.
*/

class Solution {
public:
    void recoverTree(TreeNode* root) {
        if(!root) return;
        inorder(root);
        int t = n1->val;
        n1->val = n2->val;
        n2->val = t;
    }
    void inorder(TreeNode *node) {
        if(!node) return;
        inorder(node->left);
        //visit node
        if(prev && prev->val > node->val) {
           if(!n1) n1 = prev;
           n2 = node;
        }
        prev = node;
        inorder(node->right);
    }
    TreeNode *n1 = NULL, *n2 = NULL, *prev = NULL;
};

/*
The worst solution is to use a 1D array to store the inorder results. O(n) space.
*/

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


