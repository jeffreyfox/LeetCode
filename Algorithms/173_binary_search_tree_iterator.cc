/*
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree. 
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

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

// Push all left spline to a stack.
// When popping, it a node has right subtree, push all left spline of the right child.

class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        pushLeft(root, s);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *node = s.back();
        int val = node->val;
        s.pop_back();
        if(node->right) pushLeft(node->right, s);
        return val;
    }
private:
    void pushLeft(TreeNode *root, deque<TreeNode*>& s) {
        while(root) {
            s.push_back(root);
            root = root->left;
        }
    }
    deque<TreeNode*> s; //stack
};

