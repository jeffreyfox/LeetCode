/*
Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

For example:
Given the below binary tree,

       1
      / \
     2   3

Return 6. 
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

/*
Recursive solution. 
Maximum path sum of tree rooted at x is the maximum of three cases:
 1. maximum path sum of x's left subtree (not passing x), if x's left subtree exists
 2. maximum path sum of x's right subtree (not passing x), if x's right subtree exists
 3. maximum path crossing x (x->val + maximum path from x's left child to anywhere in x's left subtree + maximum path from x's right child to anywhere in x's right subtree)
Note that the node values can be negative, so in case 3, so, some sub-paths can be length 0 (e.g. in case 3)

Therefore, we store a maximum path sum for a path originating from the root, and ending at any nodes (including the root itself), as mfr (maximum from root). The function returns the maximum path sum of the tree and also sets the mfr value by the reference.
maxPathSum(root) =  maximum of :
1) maxPathSum(root->left) if left exists
2) maxPathSum(root->right) if right exits
3) root->val (has to include root) + max(0, mfr(root->left)) + max(0, mfr(root->right)). Because the mfr can be negative for a subtree, we should compare it with 0 before addition.
Finally, we need to update the mfr of the root, which is simply:
root->val + maximum of 0, mfr(root->left), andmfr(root->right).

We initialize all values as INT_MIN.
*/

class Solution {
public:

    int maxPathSum(TreeNode* root) {
        if(!root) return 0;
        int mfr = INT_MIN; //max from root
        return maxPathHelper(root, mfr);
    }
    int maxPathHelper(TreeNode* root, int& mfr) {
        int mfr_left = INT_MIN, mfr_right = INT_MIN;
        int mp_left = INT_MIN, mp_right = INT_MIN;
        if(root->left) mp_left = maxPathHelper(root->left, mfr_left);
        if(root->right) mp_right = maxPathHelper(root->right, mfr_right);
        mfr = root->val + max(max(mfr_left, mfr_right), 0);

        int maximum = root->val + max(0, mfr_left) + max(0, mfr_right);
        maximum = max(maximum, mp_left);
        maximum = max(maximum, mp_right);
        return maximum;
    }
};

/*
A simplified version. For each subtree only calculate the maximum path originating from root, but keep a global maxSum variable that calculates the maximum path sum originating
from root for each subtree. Update the maxSum for each subtree.
*/

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        recurse(root);
        return max_path_sum;
    }
    
    // Returns the max path sum for a path that starts at root and ends at any node (could be leaf, non-leaf, or the root itself).
    int recurse(TreeNode* root) {
        if (!root) return 0;
        int max_left = recurse(root->left);
        int max_right = recurse(root->right);
        max_left = max(0, max_left);
        max_right = max(0, max_right);
        // updates the global variable.
        max_path_sum = max(max_path_sum, max_left + max_right + root->val);
        return max(max_left, max_right) + root->val;
    }
    
private:
    int max_path_sum = INT_MIN;
};

