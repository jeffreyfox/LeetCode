/*
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 1. Find the length of list, and the tail node
// 2. reduce k, if k % l == 0, then do nothing
// 3. find the new tail by calculating the residue
// 4. patch the two sub-lists

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || head->next == NULL) return head;
        if (k == 0) return head;
        
        ListNode *p = head, *tail(NULL);
        int l = 0; 
        //find length of list and tail
        while (p) {
            if(p->next == NULL) tail = p;
            p = p->next; l++;
        }
        if (k % l == 0) return head; //no rotation required
        //scan and stop at the new tail
        int cnt = l - k % l;
        p = head;
        while (cnt > 1) { // it is not > 0!
            p = p->next; cnt--;
        }
        ListNode *q = p->next; //q is the new head
        p->next = NULL; //p is new tail
        tail->next = head; //glue to segments together
        return q;
    }
};
