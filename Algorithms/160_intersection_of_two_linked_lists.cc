/*
Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
begin to intersect at node c1.


Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
*/

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

// Solution 2. Another elegant solution!
// https://leetcode.com/discuss/66203/java-solution-without-knowing-the-difference-in-len

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return NULL;
        ListNode *a = headA, *b = headB;
        while(a != b) {
            a = a ? a->next : headB;
            b = b ? b->next : headA;
        }
        return a;
    }
};


