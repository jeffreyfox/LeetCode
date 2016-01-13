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

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return helper(head, NULL);
    }
    //construct from head (inclusive) to tail (exclusive)
    TreeNode *helper(ListNode* head, ListNode *tail) {
        if(head == tail) return NULL;
        ListNode *slow = head, *fast = head;
        while(fast->next != tail && fast->next->next != tail) { //this approach returns middle of element, or the first among the two middle ones.
            slow = slow->next;
            fast = fast->next->next;
        }
        //make slow the root
        TreeNode *root = new TreeNode(slow->val);
        root->left = helper(head, slow);
        root->right = helper(slow->next, tail);
        return root;
    }
};

