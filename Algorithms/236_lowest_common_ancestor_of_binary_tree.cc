/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4

For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
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

// The tree is not BST, so we can't use value comparison. Instead, we need to examine both subtrees recursively O(n).

// Solution 1. Use two auxiliary vectors storing the search paths from root to the node. 
// Compare the two paths and find the last element both in two paths.

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || !p || !q) return NULL;
        if( !search(root, p, path1) || !search(root, q, path2)) return NULL;
        TreeNode* node = NULL;
        while(!path1.empty() && !path2.empty()) {
            TreeNode* n1 = path1.front(); path1.pop_front();
            TreeNode* n2 = path2.front(); path2.pop_front();
            if(n1 == n2) node = n1;
            else break;
        }
        return node;
    }
    //search p under subtree root
    bool search(TreeNode* root, TreeNode* p, deque<TreeNode*>& path) {
        if(!root) return false;

        path.push_back(root);
        if(root == p) return true;
        //search left and right subtree
        if(search(root->left, p, path) || search(root->right, p, path)) return true;
        path.pop_back(); //retrace
        return false;
    }
    deque<TreeNode*> path1, path2;
};

// Solution 2 without the auxiliary path vector.
// When root is equal to either node, return the root.
// Then call the function recursively for left and right subtrees. If both returns a non NULL value, that means one node is in left sub-tree, and the other is in the right
// sub-tree. In this case root is the LCA, and we return root.
// In other cases, simply return the value returned by the recursive calls.
// Reference: https://www.youtube.com/watch?v=13m9ZCB8gjw.

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;
        if (root == p || root == q) return root;
        TreeNode* lca_l = lowestCommonAncestor(root->left, p, q);
        TreeNode* lca_r = lowestCommonAncestor(root->right, p, q);
        if (lca_l && lca_r) return root;
        return (lca_l ? lca_l : lca_r);
    }
};

