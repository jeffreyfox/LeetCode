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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || head->next == NULL) return head;
        if (k == 0) return head;
        
        ListNode *p = head, *tail(NULL);
        int l = 0; 
        //find length of list and tail
        while (p) {
            if(p->next == NULL) tail = p;
            p = p->next; l++;
        }
        if (k % l == 0) return head; //no rotation required
        //scan and stop at the new tail
        int cnt = l - k % l;
        p = head;
        while (cnt > 1) { // it is not > 0!
            p = p->next; cnt--;
        }
        ListNode *q = p->next; //q is the new head
        p->next = NULL; //p is new tail
        tail->next = head; //glue to segments together
        return q;
    }
};
