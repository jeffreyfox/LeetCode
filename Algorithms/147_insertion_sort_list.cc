/*
Sort a linked list using insertion sort.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// Start from head, track the tail of already sorted list
/// If the element to be added is larger than the tail of sorted list, simply append it to the tail and move on (makes the code more efficient, 92ms => 28ms reduction!)
/// Otherwise scan from head of list and find the position to insert
/// Remember to set the next pointer of list's tail to NULL in the beginning.

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode *tail = head, *q = head->next;
        tail->next = NULL; //set tail's next to NULL
        while(q) {
            ListNode *next = q->next;
            //insert q to list from dummy to tail
            if(q->val >= tail->val) {
                tail = tail->next = q;  //update tail!
		q->next = NULL;
            } else { //search insert position from beginning
                ListNode *curr = dummy->next, *prev = dummy;
                while(curr && curr->val <= q->val) {
                    prev = curr; curr = curr->next;
                }
                prev->next = q; q->next = curr; //insert to list
            }
            q = next; //move forward
        }

        head = dummy->next;
        delete dummy;
        return head;
    }
};
