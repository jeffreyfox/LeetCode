/*
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
You should return [1, 3, 4].
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
 
 /// Solution 1. Level order traversal using two vectors (curr, next). When getting the last element of curr, insert it to result.

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        vector<TreeNode*> curr, next;
        curr.push_back(root);
        while(!curr.empty()) {
            int n = curr.size();
            for(int i = 0; i < n; i++) {
                TreeNode* node = curr[i];
                if(node->left)  next.push_back(node->left);
                if(node->right) next.push_back(node->right);
                if(i == n-1) result.push_back(node->val);
            }
            curr.swap(next);
            next.clear();
        }
        return result;
    }
};

 /// Solution 2. Level order traversal. We encounter the rightmost element at each level in two cases:
 /// (a) there's no element in the queue (queue empty)
 /// (b) the next element in the queue has higher level
 
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        queue<int> lq;
        queue<TreeNode*> nq;
        vector<int> ret;
        if(root == NULL) return ret;
        nq.push(root); lq.push(0);
        while(!nq.empty()) {
            TreeNode *node = nq.front(); nq.pop();
            int level = lq.front(); lq.pop();
            if(node->left) {
                nq.push(node->left);
                lq.push(level+1);
            }
            if(node->right) {
                nq.push(node->right);
                lq.push(level+1);
            }
            if(lq.empty() || lq.front() > level) ret.push_back(node->val);
        }
        return ret;
    }
};
