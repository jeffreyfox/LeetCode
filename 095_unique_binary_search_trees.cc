/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<TreeNode *> generateTrees(int n) {
        vector<vector<vector<TreeNode *> > > t(n+2, vector<vector<TreeNode *> >(n+2)); //table: t[i][j] is a vector of all possible trees having numbers in [i .. j-1], 1 =< i <= j <= n+1;
        int i, j, k, sz, ls, rs, ll, rr;
        for(i = 0; i <= n+1; ++i) //size 0 subtree
            t[i][i].push_back(NULL);    
        
        for(i = 1; i <= n; ++i) //size 1 subtree
            t[i][i+1].push_back(new TreeNode(i));    
        
        for(sz = 2; sz <= n; ++sz) { //size of subtree
            for(i = 1; i+sz-1 <= n; ++i) { //starts at i
                j = i+sz; //j is one pass the end
                for(k = i; k < j; ++k) { //k is the root
                    ls = t[i][k].size(); //number of possible left subtrees
                    rs = t[k+1][j].size(); //number of possible right subtrees
                    for(ll = 0; ll < ls; ++ll) {
                        for(rr = 0; rr < rs; ++rr) {
                            TreeNode* root = new TreeNode(k);
                            root->left = t[i][k][ll];
                            root->right = t[k+1][j][rr];
                            t[i][j].push_back(root);
                        }
                    }
                }
            }
        }
        return t[1][n+1]; //possible trees from [1 .. n]
    }
};
