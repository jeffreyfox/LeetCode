/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// Same as method 1, but use iterative helper function to reverse.
/// while loop invariant:
/// start:   last -> head -> ... -> ... -> tail -> next 
/// end:     last -> tail -> ... -> ... -> head -> next 

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == NULL || k == 1) return head;
        ListNode dum(0), *p(&dum); //dummy head
        p->next = head;
        ListNode *tail(NULL), *next(NULL), *last(p);
        while (head) {
            tail = head;
            int cnt = 1;
            while (cnt < k && tail) { tail = tail->next; cnt++; }
            if (!tail) break;
            next = tail->next;
            reverse(head, tail);
            last->next = tail; //tail is new head
            head->next = next; //head is new tail
            //update and move to next segment
            last = head;
            head = next;
        }
        return p->next;
    }
    void reverse(ListNode* head, ListNode* tail) {
        ListNode *next(head->next), *nextnext(NULL);
        while (head != tail) {
            nextnext = next->next;
            next->next = head; //reverse
            head = next;
            next = nextnext;
        }
    }
};
