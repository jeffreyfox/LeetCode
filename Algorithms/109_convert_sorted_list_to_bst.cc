/*
Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
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

// Recursive solution. First find middle element, then use that element as root of tree node, recursively build tree for the list segments before and after middle element, and attach as left and right child of root.
// Caveat: corner case when middle element is head of list (when only 2 nodes in list), so left subtree does not exist! Need a check (middle == head) to avoid runtime error

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if(head == NULL) return NULL;
        if(head->next == NULL) return new TreeNode(head->val); //single node
        ListNode *slow(head), *fast(head->next), *prev(NULL);
        while(fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        //use slow as root of new tree
        TreeNode *root = new TreeNode(slow->val);
        if(slow != head) { //build left child
            prev->next = NULL; //temporary set as NULL
            root->left = sortedListToBST(head);
            prev->next = slow; //set it back
        }
        root->right = sortedListToBST(slow->next); //build right child
        
        return root;
    }
};
