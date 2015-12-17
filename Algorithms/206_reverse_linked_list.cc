/*
Reverse a singly linked list.

click to show more hints.
Hint:

A linked list can be reversed either iteratively or recursively. Could you implement both?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution 1. Iterative solution. Use two pointers p and q. Temporary store q's next element.
// remember to set head->next to NULL at last step!

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head) return NULL;
        ListNode* p = head, *q = head->next; //q goes beyond p
        while(q) {
            ListNode *next = q->next;
            q->next = p;
            p = q;
            q = next;
        }
        head->next = NULL;
        return p;
    }
};

// Solution 2. Recursive solution. Set head's next pointer to NULL after calling reverse recursively for it's next. It's next will be assigned after traceback, when processing it's ancestor node.

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head) return NULL;
        if(!head->next) return head;
        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return newhead;
    }
};

