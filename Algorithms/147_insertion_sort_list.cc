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
/// If the element to be added is larger than the tail of sorted list, simply append it to the tail and move on (makes the code more efficient)
/// Otherwise scan from head of list and find the position to insert
/// Remember to set the next pointer of list's tail to NULL.

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
    ListNode* insertionSortList(ListNode* head) {
        if(!head || !head->next) return head;

        ListNode dum(0), *p(&dum);
        p->next = head;
        ListNode *tail = head; //tracks the tail of already sorted part
        ListNode *node = tail->next; //node to be inserted
        while (node) {
            int x = node->val;
            if (x >= tail->val) { tail = tail->next = node; node = node->next; continue; }

            //scan sorted part to find insertion position
            ListNode *prev = p;
            while(prev != tail && prev->next->val <= x) {
                prev = prev->next;
            }
            //insert element after prev
            ListNode *tmp = node->next; //save to tmp
            node->next = prev->next;
            prev->next = node;
            if(prev == tail) tail = node; //update tail only when reaching end!
            node = tmp;
        }
        tail->next = NULL; //set tail's next to NULL!
        return p->next;
    }
};
