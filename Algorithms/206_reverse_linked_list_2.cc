/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// Iterative solution.

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == NULL || head->next == NULL) return head; //for corner case
        ListNode *curr(head), *next(head->next), *nextnext(NULL);
        while(next) {
            nextnext = next->next; //save this temporarily
            next->next = curr; //reverse
            //move to next step
            curr = next;
            next = nextnext;
        }
        head->next = NULL; //set tail's next to null
        return curr;
    }
};
