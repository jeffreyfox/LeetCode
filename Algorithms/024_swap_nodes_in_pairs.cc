/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/// Simpler version of 25 reverse nodes in K-group, with K = 2. No need to do recursive reverse. Just one line
/// while loop invariant:
/// start:   last -> head -> tail -> next 
/// end:     last -> tail -> head -> next 
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == NULL) return head;
        ListNode dum(0), *p(&dum); //dummy head
        p->next = head;
        ListNode *tail(NULL), *next(NULL), *last(p);
        while (head) {
            tail = head->next;
            if (!tail) break;
            next = tail->next;
            tail->next = head; //reverse
            last->next = tail; //tail is new head
            head->next = next; //head is new tail
            //update and move to next segment
            last = head;
            head = next;
        }
        return p->next;
    }
};
