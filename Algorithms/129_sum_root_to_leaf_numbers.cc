/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3

The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25. 
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

// Post-order traversal using a stack.
// Keep a running partial sum, and when reaching a leaf, add the partial sum to total sum.
// First time visiting a node, add value to partial sum. When finished processing left and right subtrees, remove the value from partial sum.
// Caveats: avoid adding value to partial sum multiple times! Only do it when tag == 0.

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        int partial_sum(0), total_sum(0);
        deque<pair<TreeNode*, int> > s; //stack
        s.push_back(make_pair(root, 0));
        while(!s.empty()) {
            TreeNode *node = s.back().first;
            int tag = s.back().second;
            if(tag == 0) { //first-time, push left subtree to stack
                partial_sum = partial_sum*10 + node->val; //also calculate partial sum
                s.back().second++;
                if(node->left) s.push_back(make_pair(node->left, 0));
            } else if(tag == 1) { //second-time, push right subtree to stack
                s.back().second++;
                if(node->right) s.push_back(make_pair(node->right, 0));
            } else {  //third-time, process node
                if(!node->left && !node->right) total_sum += partial_sum;
                partial_sum /= 10; //revert to previous value without this node
                s.pop_back();
            }
        }
        return total_sum;
    }
};

// Another solution. Similar, but add pathSums when node has been added.
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        stack<pair<TreeNode*, int> > st;
        st.push(make_pair(root, 0));
        int sum = 0, pathSum = root->val;
        while(!st.empty()) {
            TreeNode* node = st.top().first;
            int tag = st.top().second;
            if(tag == 0) {
                st.top().second++;
                if(node->left) { 
                    st.push(make_pair(node->left, 0));
                    pathSum = pathSum*10 + node->left->val;
                }
            } else if(tag == 1) {
                st.top().second++;
                if(node->right) {
                    st.push(make_pair(node->right, 0));
                    pathSum = pathSum*10 + node->right->val;
                }
            } else {
                st.pop();
                if(!node->left && !node->right) sum += pathSum; //leaf node, add to sum
                pathSum /= 10;
            }
        }
        return sum;
    }
};

// 2021. Recursive solution.
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if (!root) return 0;
        return sumNumbersHelper(root, 0);
    }
    int sumNumbersHelper(TreeNode *root, int sum) {        
        int val = root->val;
        if (!root->left && !root->right) return sum*10 + val;
        int sum_left = root->left ? sumNumbersHelper(root->left, sum*10 + val) : 0;
        int sum_right = root->right ? sumNumbersHelper(root->right, sum*10 + val) : 0;
        return sum_left + sum_right;
    }
};

