/*
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 1. Traverse list using a slow and a fast pointer, find the middle element
// 2. Reverse the second half of list and return its head
// 3. start from head of first half, insert elements of second half one-by-one to first half.
// 4. set the next pointer of combined graph's tail as NULL

class Solution {
public:
   void reorderList(ListNode* head) {
        if(head == NULL || head->next == NULL) return;

        ListNode *fast(head), *slow(head);
        //slow points to middle element
        while(fast->next && fast->next->next) {
           slow = slow->next;
           fast = fast->next->next;
        }
        //now reverse sub-list headed at slow->next
        ListNode *p1(head), *p2 = reverseList(slow->next);
        slow->next = NULL; //set first list's tail properly
        //patch two sub-lists together:
        while(p2) {
            ListNode *tmp = p2->next;
            p2->next = p1->next;
            p1->next = p2;
            p1 = p2->next; //move forward p1
            p2 = tmp; //move forward p2
        }
    }
    ListNode* reverseList(ListNode *head) {
        if(head == NULL || head->next == NULL) return head;
        ListNode *tmp = head->next;
        head->next = NULL;
        ListNode *newhead = reverseList(tmp);
        tmp->next = head;
        return newhead;
    }
};
