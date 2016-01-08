/*
Given a singly linked list L: L0->L1->...->Ln-1->Ln,
reorder it to: L0->Ln->L1->Ln-1->L2->Ln-2->...

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
        if(!head || !head->next || !head->next->next) return;
        ListNode* slow = head, *fast = head;
        while(fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *p = head;
        ListNode *q = reverse(slow->next);
        slow->next = NULL;
        merge(p, q);
    }

    ListNode* reverse(ListNode *head) {
        if(!head || !head->next) return head;
        ListNode *p = head, *q = p->next;
        //p is head of new list
        while(q) {
            ListNode *tmp = q->next;
            q->next = p;
            p = q; q = tmp; //move forward
        }
        head->next = NULL;
        return p;
    }

    void merge(ListNode* p, ListNode *q) {
        ListNode *r = p;
        while(q) {
            ListNode *tmp = q->next;
            q->next = r->next;
            r->next = q;
            r = q->next; q = tmp; //move forward
        }
    }
};

