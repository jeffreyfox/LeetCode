/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Use detect cycle routine. connect A's tail to B's head, and run detect cycle II code to find the intersection point. Reset A's tail to NULL

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return NULL;
        
        ListNode *tailA(headA);
        while(tailA->next) tailA = tailA->next;
        tailA->next = headB; //connect A's tail to B
        ListNode *node = detectCycle(headA);
        tailA->next = NULL; //reset
        return node;
    }
    
    ListNode *detectCycle(ListNode *head) {
        if(head == NULL) return NULL;
        ListNode *slow = head, *fast = head;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) break;
        }
        if(!fast || !fast->next) return NULL; //no cycle detected
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};

