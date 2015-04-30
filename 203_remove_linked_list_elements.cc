/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dum(0), *dummy(&dum);
        dummy->next = head;
        ListNode *p(head), *q(dummy);
        while(p) {
            if(p->val == val) { //delete p
                q->next = p->next;
                delete p;
                p = q->next;
            } else {
                q = p;
                p = p->next;
            }
        }
        return dummy->next;
    }
};
