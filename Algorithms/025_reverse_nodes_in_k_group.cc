/*
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/*
Solution 1. Iterative.
Determine the head and tail of each segment, and use a helper function to reverse it, and attach it to original list. The helper funtion
Uses a dummy head.
while loop invariant:
 start:   p1 -> [ p2 -> ... -> p3 ] -> p4 
 end:     p1 -> [ p3 -> ... -> p2 ] -> p4
*/

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head || k <= 1) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *p1 = dummy, *p2 = head;
       // p1 -> [ p2 -> ... -> p3 ] -> p4 => p1 -> p3 -> ... -> p2 -> p4
        while(p2) {
            int count = k;
            ListNode *p3 = p2, *p4 = NULL;
            while(count > 1 && p3) {
                count--;
                p3 = p3->next;
            }
            if(!p3) break; //not enough elements to reverse
            p4 = p3->next;
            //now reverse p2 -> ... -> p3
            ListNode *curr = p2, *next = curr->next, *nextnext = NULL;
            while(curr != p3) {
                nextnext = next->next; // save it to tmp
                next->next = curr; //reverse 
                curr = next; //move forward
                next = nextnext; //move forward
            }
            //now connects p1 -> p3 and p2 -> p4
            p1->next = p3; p2->next = p4;
            //back to loop
            p1 = p2; p2 = p4;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

/* 
Solution 2. Same as method 1, but use iterative helper function to reverse.
*/

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
/*  
    //A slightly different reverse version
    void reverse(ListNode* head, ListNode* tail) {
        ListNode *next(head->next);
        while (head != tail) {
            ListNode* tmp = next->next; //tmp stores next->next 
            next->next = head; //reverse
            head = next;
            next = tmp;
        }
    }
*/
};
