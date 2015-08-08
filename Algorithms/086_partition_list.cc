/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Use two dummy heads for sublist < x and sublist >=x
// when finish, patch two lists together

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
       if (head == NULL) return head;
       ListNode dum1(0), dum2(0), *p1(&dum1), *p2(&dum2);
       ListNode *q1(p1), *q2(p2);
       ListNode *curr = head;
       while(curr) {
           if(curr->val < x) { q1->next = curr; q1 = q1->next; }
           else { q2->next = curr; q2 = q2->next; }
           curr = curr->next;
       }
       if(p1->next == NULL) return p2->next;
       q1->next = p2->next;
       if(p2->next) q2->next = NULL;
       return p1->next;
    }

};
