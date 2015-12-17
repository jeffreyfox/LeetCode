/*
Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution using a dummy head

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if(!head) return NULL;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode *p = dummy, *q = dummy->next;
        //q is one step ahead of p
        while(q) {
            if(q->val == val) { //delete q
                p->next = q->next;
                delete q;
                q = p->next;
            } else { //just move forward
                p = p->next;
                q = q->next;
            }
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

