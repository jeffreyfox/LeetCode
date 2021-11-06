/*
Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
   0      _4       7       9
         /  \
         3   5

For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
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

// Take advantage of the property of BST. Do it recursively.
// If root is same as either nodes, then root is LCA.
// If the two nodes are one different sides of root, then root is LCA.
// Otherwise recursively go to root's left or right subtree depending on which side of the root the nodes are at.
// Time complexity is O(h), where h is the height of tree.

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || !p || !q) return NULL;
        return LCA(root, p, q);
    }
    TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;
        if(p == root || q == root) return root; //one is equal to root
        if((p->val < root->val) ^ (q->val < root->val)) return root; //lying on two sides of root
        if(p->val < root->val) return LCA(root->left, p, q);
        else return LCA(root->right, p, q);
    }
};

// 2021.
// Similar idea with iteration.
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) return nullptr;
        TreeNode *curr = root;
        int lo = min(p->val, q->val);
        int hi = max(p->val, q->val);
        while (curr) {
            if (curr == p) return p;
            if (curr == q) return q;
            if (curr->val < lo) curr = curr->right;
            else if (curr->val > hi) curr = curr->left;
            else return curr;
        }
        // Something wrong
        return nullptr;
    }
};

