/*
Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [3,2,1].

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        postorder(root, ret);
        return ret;
    }
    void postorder(TreeNode *root, vector<int>& ret) {
        if(!root) return;
        postorder(root->left, ret);
        postorder(root->right, ret);
        ret.push_back(root->val);
    }
};

// Iterative solution using a stack (and a tag for each node tracking how many times it has been pushed_to stack.
// Use pair instead of struct for simplicity.
// Slightly improved version. Avoid frequent pop and push operations, instead just update(increment) top's tag value.
// Typically each node will be checked three times, each time the value associated with it will be incremented.
// 1. The 1st time it is checked, push left child to stack if any
// 2. The 2nd time it is checked, push right child to stack if any
// 3. The 3rd time it is checked, we are done with the sub-trees so we can save the node to output and pop it out.

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<pair<TreeNode*, int> > st; //stack
        st.push_back(make_pair(root, 0));
        TreeNode* node;
        while(!st.empty()) {
            int tag = ++st.back().second;
            node = st.back().first;
            if(tag == 1) {
                if(node->left) st.push_back(make_pair(node->left, 0));
            } else if(tag == 2) {
                if(node->right) st.push_back(make_pair(node->right, 0));
            } else {
                result.push_back(node->val);
                st.pop_back();
            }
        }
        return result;
    }
};

// Iterative solution without tag in each node, instead use a pre pointer pointing to the previous node visited, by checking (1) whether previous node is the nodes left or right child, and (2) whether left or right child exist, we determine what we do next.
// There are three cases typically:
// 1. 1st time a node is checked, pre does not equal either children (if any).
// 2. 2nd time a node is checked, we just visited left sub-tree, so pre == node->left
// 3. 3rd time a node is checked, we just visited right sub-tree, so pre == node->rights
// There are also cases where left and/or right child is empty.
// If left child exists and pre is not equal to either children, then we push
// For correct comparison, pre should be initialized as not a NULL value, so we can initialize it as root.

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<TreeNode*> st;
        st.push_back(root);
        TreeNode *pre = root, *node = NULL;
        while(!st.empty()) {
            node = st.back();
            if(node->left && node->left != pre && node->right != pre) {
                st.push_back(node->left);
            } else if(node->right && node->right != pre) {
                st.push_back(node->right);
            } else {
                result.push_back(node->val);
                pre = node;
                st.pop_back();
            }
        }
        return result;
    }
};


