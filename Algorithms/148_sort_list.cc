/*
Sort a linked list in O(n log n) time using constant space complexity.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// top-down merge sort
// when finding the middle element, fast is initialized as head->next, not head, to avoid infinite loop in corner cases (only two nodes).

class Solution {
public:
    ListNode* sortList(ListNode* head) {
         if(!head || !head->next) return head;
         ListNode *slow(head), *fast(head->next);
         while(fast && fast->next) {
             slow = slow->next;
             fast = fast->next->next;
         }
         ListNode *head2 = slow->next;
         slow->next = NULL;
         return merge(sortList(head), sortList(head2));
    }
    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode dum(0), *p(&dum), *tail(p);
        while(head1 && head2) {
            if (head1->val <= head2->val) {
                tail->next = head1;
                head1 = head1->next;
                tail = tail->next;
            } else {
                tail->next = head2;
                head2 = head2->next;
                tail = tail->next;
            }
        }
        tail->next = head1 ? head1 : head2;
        return p->next;
    }
};
