/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// Determine the head and tail of each segment, and use a helper function to reverse it, and attach it to original list. The helper funtion
/// uses recursive algorithm to reverse a segment
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
    // reverse a list segment (head -> ... -> tail), which becomes (tail -> ... -> head)
    void reverse(ListNode* head, ListNode* tail) {
        if(head == tail) return;
        ListNode *next = head->next;
        reverse(next, tail);
        next->next = head;
    }
};
