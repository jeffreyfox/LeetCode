/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,3,2].

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

// Recursive solution (easy).

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        inorder(root, ret);
        return ret;
    }
    void inorder(TreeNode* root, vector<int>& ret) {
        if(!root) return;
        if(root->left) inorder(root->left, ret);
        ret.push_back(root->val);
        if(root->right) inorder(root->right, ret);
    }
};

// Iterative solution using a stack (and a tag indicating the number of times an element appears in stack).
// Slightly different version with modified control flow with tag.

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<pair<TreeNode*, int> > st; //stack
        st.push_back(make_pair(root, 0));
        while(!st.empty()) {
            TreeNode *node = st.back().first;
            int tag = ++st.back().second;
            if(tag == 1) {
                if(node->left) st.push_back(make_pair(node->left, 0));
            } else {
                result.push_back(node->val);
                st.pop_back();
                if(node->right) st.push_back(make_pair(node->right, 0));
            }
        }
        return result;
    }
};

// Another iterative solution by pushing left spline in the stack
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<TreeNode*> st; //stack
        while(root) {
            st.push_back(root);
            root = root->left;
        }
        while(!st.empty()) {
            TreeNode* node = st.back(); st.pop_back();
            result.push_back(node->val);
            node = node->right;
            while(node) {
                st.push_back(node);
                node = node->left;
            }
        }
        return result;
    }
};

// Morris traversal O(n) without using a stack or recursive calls.
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        TreeNode *node = root;
        while(node) {
            if(!node->left) {
                result.push_back(node->val);
                node = node->right;
            } else {
                TreeNode *child = node->left;
                while(child->right != NULL && child->right != node) child = child->right;
                if(child->right == NULL) {
                    child->right = node; // first time, modify right pointer
                    node = node->left; //move to left child
                } else {
                    child->right = NULL; //second time, reset right pointer to NULL
                    result.push_back(node->val);
                    node = node->right;
                }
            }
        }
        return result;
    }
};

// Morris traversal with a slightly different while loop (visit node in the end of loop body)
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        TreeNode *node = root;
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
            //visit node
            result.push_back(node->val);
            node = node->right;
        }
        return result;
    }
};


