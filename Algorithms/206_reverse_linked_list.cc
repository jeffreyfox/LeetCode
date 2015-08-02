/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Recursive solution
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == NULL) return head; //for corner case
        if(head->next == NULL) return head; // end of recursive calls
        ListNode *next = head->next;
        head->next = NULL; //set head's next as null
        ListNode *newhead = reverseList(next);
        next->next = head;
        return newhead;
    }
};
