/*
Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.

Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// O(1) solution, just link current node's pointer to the next next node, delete the next node.
/// For safety, do the sanity check to ensure node is not null, or last node in the list.

class Solution {
public:
    void deleteNode(ListNode* node) {
        //first do some sanity check
        if(node == NULL || node->next == NULL) return;
        node->val = node->next->val;
        ListNode* t = node->next;
        node->next = t->next;
        delete t;
    }
};
