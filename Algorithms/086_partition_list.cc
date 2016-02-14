/*
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// No dummy heads, two sub-lists for < x and >= x
// when finish, patch two lists together, and remember to set list tail's next pointer to NULL!

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if(!head || !head->next) return head;
        //p1 .. q1 < x, p2 .. q2 >= x
        ListNode *p1(NULL), *q1(NULL), *p2(NULL), *q2(NULL);
        ListNode *curr = head;
        while(curr) {
            if(curr->val < x) {
                if(!p1) p1 = q1 = curr; //first one
                else q1 = q1->next = curr; 
            } else {
                if(!p2) p2 = q2 = curr; //first one
                else q2 = q2->next = curr; 
            }
            curr = curr->next;
        }
        if(q1) q1->next = p2; //connect the two
        if(q2) q2->next = NULL; //set tail to NULL!
        return p1 ? p1 : p2;
    }
};
