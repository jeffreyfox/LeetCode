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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Be careful when using bit operator!! if(level & 1 == 0) is wrong!, 1 == 0 has higher priority, should use if (!(level&1)).

/// Using two stacks. Swap the two when exhausting one level. Use a level tag to track polarity, which determines whether left or right subtree gets pushed to stack first
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > ret;
        if(!root) return ret;
        deque<TreeNode*> current, next;
        int level = 0;
        current.push_back(root);
        ret.push_back(vector<int>());
        while(!current.empty() || !next.empty()) { //break when both current and next are empty
            if(current.empty()) { // when exhausing current level ...
                current.swap(next); //swap current and next
                ret.push_back(vector<int>());
                level ++;
            }
            TreeNode *node = current.back();  current.pop_back();
            if(level % 2 == 0) {
                if(node->left) next.push_back(node->left);
                if(node->right) next.push_back(node->right);
            } else {
                if(node->right) next.push_back(node->right);
                if(node->left) next.push_back(node->left);
            }
            ret[level].push_back(node->val);
        }
        return ret;
    }
};

// Solution with 2 stacks, and two loops
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        //stack for two levels
        vector<TreeNode*> current, next;
        int level = 0; //level and parity
        current.push_back(root);
        while(!current.empty()) {
            result.push_back(vector<int>()); //new level
            //user current as stack
            for(vector<TreeNode*>::reverse_iterator it = current.rbegin(); it != current.rend(); ++it) {
                TreeNode *node = *it;
                if(level % 2 == 0) { //l=>r
                    if(node->left) next.push_back(node->left);
                    if(node->right) next.push_back(node->right);
                } else {
                    if(node->right) next.push_back(node->right);
                    if(node->left) next.push_back(node->left);
                }
                //insert to result
                result[level].push_back(node->val);
            }
            current.swap(next);
            next.clear();
            level++;
        }
        return result;
    }
};
