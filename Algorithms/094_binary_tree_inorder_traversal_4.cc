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

// Morris traversal O(n) without using a stack or recursive calls.

class Solution {
public:
    struct Element {
        TreeNode *node;
        int tag;
        Element(TreeNode *n, int t) : node(n), tag(t) {}
        Element() : node(NULL), tag(-1) {}
    };
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        deque<Element> s; //stack
        s.push_back(Element(root, 0));
        while(!s.empty()) {
            TreeNode *node = s.back().node;
            int tag = s.back().tag;
            s.pop_back();
            if(tag == 0) { //first time seen, process left subtrees
                s.push_back(Element(node, 1));
                if(node->left) s.push_back(Element(node->left, 0));
            } else { //second time seen, add to result, and process right
                ret.push_back(node->val);
                if(node->right) s.push_back(Element(node->right, 0));
            }
        }
        return ret;
    }
};