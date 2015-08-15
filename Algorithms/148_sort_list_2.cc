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

// bottom-up merge sort, using a queue
// Sort is unstable if number of nodes are not power of 2!

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        deque<ListNode*> q;
        ListNode *p = head;
        //push nodes into queue, also set next to NULL (break into many single-node lists)
        while(p) {
            q.push_back(p);
            ListNode *next = p->next;
            p->next = NULL;
            p = next;
        }
        ListNode dum(0);
        p = &dum; //dummy node
        while(!q.empty()) {
            ListNode* n1 = q.front(); q.pop_front();
            if(q.empty()) return n1;
            ListNode *n2 = q.front(); q.pop_front();
            q.push_back(merge(n1, n2));
        }
        return NULL; //something wrong
    }
    //merge two sorted, non-empty lists
    ListNode* merge(ListNode *head1, ListNode *head2) {
        ListNode dum(0), *p(&dum), *tail(p);
        while(head1 && head2) {
            if(head1->val <= head2->val) {
                tail->next = head1;
                head1 = head1->next;
            } else {
                tail->next = head2;
                head2 = head2->next;
            }
            tail = tail->next;
        }
        tail->next = head1 ? head1 : head2;
        return p->next;
    }
};
