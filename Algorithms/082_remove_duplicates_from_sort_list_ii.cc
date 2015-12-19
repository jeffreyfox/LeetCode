/*
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// use two pointers. Also dummy head, because head might be deleted.

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;

        ListNode *p = dummy, *q = p->next;
        //p is tail of processed list, q is its next, r is one node past the last duplicated entry.
        while(q) {
            ListNode* r = q->next;
            while(r && r->val == q->val) r = r->next;
            //r is either null or first entry not equal to q
            if(r == q->next) { //no duplicated entry
                p = q;
                q = r; //just move forward
                continue;
            }
            //then delete everything from q to r's ancestor
            while(q != r) {
                ListNode * t = q;
                delete t;
                q = q->next;
            }
            //after loop q == r
            p->next = q;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};
