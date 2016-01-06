/*
Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
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

// Dynamic programming using a 2D array. The trick is to generate the right subtree by using a createNew function with a delta value.

class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n < 0) return vector<TreeNode*>();
        if(n == 0) return vector<TreeNode*>();
        vector<vector<TreeNode*> > dp(n+1); //dp[i]: solutions for tree of size i
        dp[0].push_back(NULL);
        for(int i = 1; i <= n; ++i) { //check tree of size i
            for(int k = 1; k <= i; ++k) { //make k as root
                for(auto l : dp[k-1]) { //construct left subtree
                    for(auto r : dp[i-k]) { //construct right subtree
                        TreeNode *root = new TreeNode(k);
                        root->left = l;
                        root->right = createNew(r, k);
                        dp[i].push_back(root);
                    }
                }
            }
        }
        return dp[n];
    }
    TreeNode* createNew(TreeNode* root, int delta) {
        if(!root) return NULL;
        TreeNode* nr = new TreeNode(root->val+delta); //new root
        nr->left = createNew(root->left, delta);
        nr->right = createNew(root->right, delta);
        return nr;
    }
};

