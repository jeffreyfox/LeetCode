/*
Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:

    Given target value is a floating point.
    You may assume k is always valid, that is: k ≤ total nodes.
    You are guaranteed to have only one unique set of k values in the BST that are closest to the target.

Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

Hint:

    Consider implement these two helper functions:
        getPredecessor(N), which returns the next smaller node to N.
        getSuccessor(N), which returns the next larger node to N.
    Try to assume that each node has a parent pointer, it makes the problem much easier.
    Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
    You would need two stacks to track the path in finding predecessor and successor node separately.
*/

// First build the stack storing search path for predecessor and successor of target. For predecessor, only insert into stack nodes smaller than target during search, and likewise for successor. nodes equal to the target will be inserted to predecessor (to break tie and avoid duplicated results returned). Then implement the nextSucc and nextPred function to return the next larger/smaller value to target, by poppping/pushing elements from/to stack. Do a merging routine similar to the merge sort to establish the order of k values.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> result(k, 0);
        if(!root) return result;
        //build stack for predecessor path
        TreeNode *node = root;
        while(node) {
            if(target < node->val) node = node->left;
            else {
                pred.push(node);
                node = node->right;
            } 
        }
        //build stack for successor path
        node = root;
        while(node) {
            if(target >= node->val) node = node->right;
            else {
                succ.push(node);
                node = node->left;
            }
        }

        TreeNode *p = nextPred(), *s = nextSucc();
        for(int i = 0; i < k; ++i) {
           if(!p) { result[i] =  s->val; s = nextSucc(); } 
           else if(!s) { result[i] =  p->val; p = nextPred(); }
           else if(target - p->val > s->val - target) { result[i] =  s->val; s = nextSucc(); } 
           else { result[i] =  p->val; p = nextPred(); }
        }
        return result;
    }

    TreeNode* nextPred() {
        if(pred.empty()) return NULL;
        TreeNode* node = pred.top(); pred.pop();
        TreeNode *tmp = node->left;
        while(tmp) {
            pred.push(tmp); 
            tmp = tmp->right;
        }
        return node;
    }

    TreeNode* nextSucc() {
        if(succ.empty()) return NULL;
        TreeNode* node = succ.top(); succ.pop();
        TreeNode *tmp = node->right;
        while(tmp) {
            succ.push(tmp); 
            tmp = tmp->left;
        }
        return node;
    }

    stack<TreeNode*> pred, succ; //stack for predecessor and successor paths
};

