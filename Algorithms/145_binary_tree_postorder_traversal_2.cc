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

// Iterative solution using a stack (and a tag for each node tracking how many times it has been pushed_to stack.

class Solution {
public:
    struct Element {
        TreeNode *node;
        int tag;
        Element(TreeNode *n, int t) : node(n), tag(t) {}
    };
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        deque<Element> s; //stack
        s.push_back(Element(root, 0));
        while(!s.empty()) {
            TreeNode *node = s.back().node;
            int tag = s.back().tag;
            s.pop_back();
            if(tag == 0) { //first time, process left subtree
                s.push_back(Element(node, 1));
                if(node->left) s.push_back(Element(node->left, 0));
            } else if (tag == 1) { //second time, process right subtree
                s.push_back(Element(node, 2));
                if(node->right) s.push_back(Element(node->right, 0));
            } else { //third time, insert to ret
                ret.push_back(node->val);
            }
        }
        return ret;
    }
};
