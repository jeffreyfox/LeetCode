/*
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:

[
  [3],
  [9,20],
  [15,7]
]
*/

/// Using two stacks. Swap the two when exhausting one level. Use a level tag to track polarity, which determines whether left or right subtree gets pushed to stack first

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > ret;
        if(!root) return ret;
        deque<TreeNode*> q1, q2;
        int level = 0;
        q1.push_back(root);
        while(!q1.empty() || !q2.empty()) { //break when both q1 and q2 are empty
            if(q1.empty()) { 
                q1.swap(q2); //swap q1 and q2 when exhausing one level
                level ++;
            }
            TreeNode *node = q1.back();  q1.pop_back();
            if(level == ret.size()) ret.push_back(vector<int>());
            ret[level].push_back(node->val);
            if(level % 2 == 0) {
                if(node->left) q2.push_back(node->left);
                if(node->right) q2.push_back(node->right);
            } else {
                if(node->right) q2.push_back(node->right);
                if(node->left) q2.push_back(node->left);
            }
        }
        return ret;
    }
};
