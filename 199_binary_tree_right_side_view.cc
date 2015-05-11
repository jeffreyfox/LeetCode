/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
 /// Level order traversal. We encounter the rightmost element at each level in two cases:
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
