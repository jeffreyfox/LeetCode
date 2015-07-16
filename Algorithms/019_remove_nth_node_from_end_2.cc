/// Without dummy head. Need to check if head is to be deleted

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
        ListNode *front(head), *back(head), *p(NULL);
        for(int i = 0; i < n-1; ++i) front = front->next;
        while(front->next) {
            p = back;
            front = front->next;
            back = back->next;
        }
        //delete back
        if(p == NULL) head = back->next;
        else p->next = back->next;
        delete back;
        return head;
    }
};
