/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Use dummy head. Add additional node if final carry = 1.
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;
        ListNode dum(0), *p(&dum), *q(p);
        int carry = 0;
        while(l1 || l2) {
            int v1 = (l1 == NULL) ? 0 : l1->val;
            int v2 = (l2 == NULL) ? 0 : l2->val;
            int sum = v1+v2+carry;
            q->next = new ListNode(sum % 10);
            carry = sum / 10;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
            q = q->next;
        }
        if (carry == 1) q->next = new ListNode(carry);
        return p->next;
    }
};
