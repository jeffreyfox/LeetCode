/// Use dummy head node
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dum(0), *dummy(&dum);
        dummy->next = head;
        ListNode *front(dummy), *back(dummy), *p(NULL);
        for(int i = 0; i < n-1; ++i) front = front->next;
        while(front->next) {
            p = back;
            front = front->next;
            back = back->next;
        }
        //delete back
        p->next = back->next;
        delete back;
        return dummy->next;
    }
};
