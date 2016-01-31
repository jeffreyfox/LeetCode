/*
Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

Examples:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its vertical order traversal as:
[
  [9],
  [3,15],
  [20],
  [7]
]
Given binary tree [3,9,20,4,5,2,7],
    _3_
   /   \
  9    20
 / \   / \
4   5 2   7
return its vertical order traversal as:
[
  [4],
  [9],
  [3,5,2],
  [20],
  [7]
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

// Using level order traversal, keep track of lowest and highest positions. Use a map to store the results, then shift the results to vector

class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        unordered_map<int, vector<int> > dict;
        int lo(INT_MAX), hi(INT_MIN);
        vector<pair<TreeNode*, int> > curr, next;
        curr.push_back(make_pair(root, 0));
        while(!curr.empty()) {
            int n = curr.size();
            for(int i = 0; i < n; i++) {
                TreeNode *node = curr[i].first;
                int pos = curr[i].second;
                dict[pos].push_back(node->val);
                if(pos < lo) lo = pos;
                if(pos > hi) hi = pos;
                if(node->left) next.push_back(make_pair(node->left, pos-1));
                if(node->right) next.push_back(make_pair(node->right, pos+1));
            }
            curr.swap(next);
            next.clear();
        }
        //copy results in map to vector
        result.resize(hi-lo+1);
        for(int i = 0; i <= hi-lo; i++) 
            result[i] = dict[i+lo];
        return result;
    }
};
