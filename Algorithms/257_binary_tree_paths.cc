/*
 Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5

All root-to-leaf paths are:

["1->2->5", "1->3"]
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

// Standard dfs solution (recursive). The numbers can be negative.
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        string tmp;
        if(!root) return result;
        dfs(root, tmp, result);
        return result;
    }
    void dfs(TreeNode *root, string tmp, vector<string>& result) {
        tmp += num2str(root->val);
        if(!root->left && !root->right) {
            result.push_back(tmp);
            return;
        }
        if(root->left) dfs(root->left, tmp+"->", result);
        if(root->right) dfs(root->right, tmp+"->", result);
    }

    string num2str(int n) {
        if(n == 0) return "0";
        int sign = n > 0 ? 1 : -1;
        n = abs(n);
        string s;
        while(n) {
            char c = n % 10 + '0';
            s = c + s;
            n /= 10;
        }
        if(sign == -1) s = "-" + s;
        return s;
    }
};
