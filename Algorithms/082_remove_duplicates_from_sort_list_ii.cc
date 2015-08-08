/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// When visiting a node, see if it has the same value as next, if yes, set removal tag of next elements
// Use a dummy head

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        bool isDup = false, isDupNext = false;
        ListNode dum(0), *p(&dum);
        p->next = head;
        ListNode *curr = head, *prev(p), *next(NULL);
        while (curr) {
            isDup = isDupNext;
            next = curr->next;
            if(next && next->val == curr->val) {
               isDupNext = true; //mark next as isdup
               isDup = true;
            } else { //not the same
               isDupNext = false;
            }
            if (isDup) { //remove current node
               ListNode *tmp = curr;
               prev->next = next;  curr = next;
               delete tmp;
            } else {
                prev = curr;
                curr = next;
            }
        }
        return p->next;
    }
};
