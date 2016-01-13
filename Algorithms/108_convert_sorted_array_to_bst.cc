/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
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

// Recursive solution

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.empty()) return NULL;
        int n = nums.size();
        return convert(nums, 0, n-1);
    }
    
    TreeNode* convert(vector<int>& nums, int lo, int hi) {
        if(lo > hi) return NULL;
        int mid = (lo+hi)/2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = convert(nums, lo, mid-1);
        root->right = convert(nums, mid+1, hi);
        return root;
    }
};

// A variant. Range is [beg, end)

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size());
    }

    TreeNode* helper(vector<int>& nums, int beg, int end) {
        if(beg >= end) return NULL;
        int mid = (beg+end)/2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = helper(nums, beg, mid);
        root->right = helper(nums, mid+1, end);
        return root;
    }
};

