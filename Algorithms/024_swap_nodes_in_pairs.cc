/*
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution 1. Iterative solution. Use a dummy head and two pointers.

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        //p is tail of processed list part
        ListNode *p = dummy, *q = p->next;
        //swap q and q->next
        while(q && q->next) {
            ListNode *r = q->next;
            q = r->next; //move to next
            r->next = p->next;
            p->next = r;
            p = r->next; //move forward
            p->next = q;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

// Solution 2. Recursive solution.
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *p = head->next, *q = p->next;
        p->next = head;
        head->next = swapPairs(q);
        return p;
    }
};

