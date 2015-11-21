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

/// Classical solution using a queue

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Solution using one queue and a customized struct Element

class Solution {
public:
    struct Element {
        TreeNode *node;
        int level;
        Element(TreeNode *n, int l) : node(n), level(l) {}
    };
    
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > ret;
        if(!root) return ret;
        deque<Element> q; //queue
        q.push_back(Element(root, 0));
        while(!q.empty()) {
            TreeNode *node = q.front().node;
            int level = q.front().level;
            q.pop_front();
            if(level == ret.size()) ret.push_back(vector<int>());
            ret[level].push_back(node->val);
            if(node->left) q.push_back(Element(node->left, level+1));
            if(node->right) q.push_back(Element(node->right, level+1));
        }
        return ret;
    }
};

// Solution using one queue and std::pair (4ms)
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        deque<pair<TreeNode*, int> > q; //include level
        q.push_back(make_pair(root, 0));
        int currLevel = -1;
        while(!q.empty()) {
            TreeNode *node = q.front().first;
            int level = q.front().second;
            q.pop_front();
            if(level > currLevel) { 
                result.push_back(vector<int>());  //start a new level
                currLevel = level;
            }
            if(node->left) q.push_back(make_pair(node->left, level+1));
            if(node->right) q.push_back(make_pair(node->right, level+1));
            result[currLevel].push_back(node->val);
        }
        return result;
    }
};

// Solution using 2 vectors (queues), one for current level and one for next level (8ms)
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        vector<TreeNode*> current, next;
        current.push_back(root);
        while(!current.empty()) {
            result.push_back(vector<int>()); //start a new level (for current)
            for(auto node : current) {
                if(node->left) next.push_back(node->left);
                if(node->right) next.push_back(node->right);
                result.back().push_back(node->val); //push value to result
            }
            current.swap(next);
            next.clear();
        }
        return result;
    }
};

