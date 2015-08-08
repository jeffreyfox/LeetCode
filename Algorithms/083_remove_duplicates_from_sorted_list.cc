/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Since head will never be removed, do not need a dummy head pointer

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        int last = head->val;
        ListNode *prev = head, *curr = head->next;
        while (curr) {
            if(curr->val == last) {
                ListNode *tmp = curr;
                curr = prev->next = curr->next;
                delete tmp;
            } else {
                last = curr->val;
                prev = curr;
                curr = curr->next;
            }
        }
        return head;
    }
};
