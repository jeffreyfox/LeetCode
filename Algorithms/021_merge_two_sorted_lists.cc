/*
Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Use dummy head, and a tail pointer to track end of sorted list.
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0), *p(&dummy);
        ListNode *tail = p;
        while(l1 && l2) {
            if(l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        if(l1) tail->next = l1;
        else tail->next = l2;
        return p->next;
    }
};

// 2021.11
// No tail pointer. One pass but creates new nodes instead of reusing existing ones. Wrong solution.
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode tmp(0);
        ListNode *dummy(&tmp);
        ListNode *p = dummy;
        while (l1 || l2) {
            if (l1 == nullptr) {
                p->next = new ListNode(l2->val);
                l2 = l2->next;
            } else if (l2 == nullptr) {
                p->next = new ListNode(l1->val);
                l1 = l1->next;
            } else if (l1->val < l2->val) {
                p->next = new ListNode(l1->val);
                l1 = l1->next;
            } else {
                p->next = new ListNode(l2->val);                
                l2 = l2->next;
            }
            p = p->next;
        }
        return dummy->next;
    }
};
