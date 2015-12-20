/*
You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Use dummy head. Add additional node if final carry = 1.
// Caveats:
// 1. Don't forget to move l1 and l2 forward!
// 2. Last step, scheck if carry > 0, not carry > 1 !

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0), *p(dummy);
        int sum = 0, carry = 0;
        while(l1 || l2) {
            int v1 = l1 ? l1->val : 0;
            int v2 = l2 ? l2->val : 0;
            sum = v1 + v2 + carry;
            carry = sum / 10;
            sum %= 10;
            p->next = new ListNode(sum);
            p = p->next;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        if(carry > 0) p->next = new ListNode(carry);
        
        p = dummy->next;
        delete dummy;
        return p;
    }
};


