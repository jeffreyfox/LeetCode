/*
Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
Given n will always be valid.
Try to do this in one pass. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// Solution 1. Use dummy head node. Two while loops.
/// The idea is to use two pointers, front and back.
/// First, let front pointer move n steps forward.
/// Then, let both front and back pointers move at the same pace. When the front reaches the tail, the back->next is the one to be removed.
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode tmp(0);
        ListNode *dummy = &tmp;
        dummy->next = head;
        ListNode *front = dummy, *back = dummy;
        // Let front move n steps forward.
        while (n > 0) {
            front = front->next;
            --n;
        }
        // Now move front and back together until front reaches the tail, then back->next is the node to be removed.
        while (front->next) {
            front = front->next;
            back = back->next;
        }
        // Remove back->next
        ListNode *p = back->next;
        back->next = p->next;
        delete p;
        return dummy->next;
    }
};

/// Solution 2. Same idea, but one pass (slightly simplified code).

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *first(dummy), *last(dummy);
        while(last->next) {
            last = last->next;
            if(--n < 0) first = first->next;
        }
        
        //delete first->next;
        ListNode* tmp = first->next;
        first->next = tmp->next;
        delete tmp;
        //return new head
        head = dummy->next;
        delete dummy;
        return head;
    }
};


