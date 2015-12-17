/*
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
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

// Caveat: This is different from the maxDepth problem!. There are several cases:
// 1. single node (no left or right children): minD = 1;
// 2. only left child: minD = 1 + minD of left
// 3. only right child: minD = 1 + minD of right
// 4. both childs: mindepth = 1 + min(minD of left, minD of right)
// The reason for the difference is that if a node has one empty subtree, and the other is not empty, the empty subtree does not count as the mininum depth path.

class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        int minD = 0;
        if(!root->left)  minD = minDepth(root->right);
        else if(!root->right) minD = minDepth(root->left);
        else minD = min(minDepth(root->left), minDepth(root->right));
        return minD+1;
    }
};

// An alternative solution
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        if((root->left == NULL) ^ (root->right == NULL))  //only one subtree is not null
            return root->left ? minDepth(root->left)+1 : minDepth(root->right)+1;
        else //either both are null, or none are null
            return minD = min(minDepth(root->left), minDepth(root->right)) + 1;
    }
};

// The following solution is WRONG!
class Solution {
public:
    int minDepth(TreeNode* root) { //wrong solution. fails when left is NULL, and right is not
        if(!root) return 0;
        int d = 1;
        if(root->left) d = minDepth(root->left) + 1;
        if(root->right) d = min(d, minDepth(root->right)+1);
        return d;
    }
};


