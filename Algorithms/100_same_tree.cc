/*
Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value. 
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

// Do it recursively.
// Caveats: remember to compare the values of the two nodes!

class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if((p == NULL) ^ (q == NULL)) return false; //one null, the other not
        if(p == NULL) return true; //both are null
        //both are not null 
        return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

//alternative solution
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if(p == NULL) return q == NULL;
        if(q == NULL) return false;
        //both are not null 
        return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

