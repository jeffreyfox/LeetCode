/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// Use a counter k, one pass.
// 1. When reached (m-1)-th element, save the curr and next node as pa and pb:
// 2. when k between m and n-1, do reverse
// 3. when k = n, patch two segments together using pa and pb.
// Use a dummy head pointer
//  1 => .. => m-1 => m => ... => n => n+1 => ...
//              pa   pb           curr  next
//       ... => pa => curr => pb => next => ...

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(head == NULL || head->next == NULL) return head;
        if(m == n) return head;

        ListNode dum(0), *p(&dum);
        p->next = head;
        ListNode *curr(p), *next(NULL);
        ListNode *pa(NULL), *pb(NULL);
        for (int k = 0; curr != NULL && k <= n; k++) {
            if (k < m-1)  curr = curr->next;
            else if (k == m-1)  {
                pa = curr;
                pb = curr->next;
                curr = curr->next;
                next = curr->next; //init next at this point
            }
            else if (k < n) { // do reverse: change curr->next to point to curr
                ListNode *nextnext = next->next;  //store in temp variable
                next->next = curr;
                curr = next;  //update curr
                next = nextnext; //update next
            } else if (k == n) { //connect two list segments
                pa->next = curr;
                pb->next = next;
            }
        }
        return p->next;
    }

};
