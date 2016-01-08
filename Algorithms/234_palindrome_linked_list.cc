/*
Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// 4 steps:
// 1. Find middle element
// 2. reverse second half of array
// 3. compare second half with first half
// 4. recover the original linked list (reverse second part again and connect to first part)

/// O(n) time, O(1) space

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(!head || !head->next) return true;
        ListNode *slow = head, *fast = head;
        while(fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *second = reverse(slow->next);
        ListNode *p = head, *q = second;
        bool result = true;
        while(q) {
            if(p->val != q->val) { result = false; break; }
            p = p->next; q = q->next;
        }
        slow->next = reverse(second);
        return result;
    }
    ListNode* reverse(ListNode *head) {
        if(!head || !head->next) return head;
        ListNode *p = head, *q = head->next;
        p->next = NULL;
        while(q) {
            ListNode *tmp = q->next;
            q->next = p;
            p = q; q = tmp;
        }
        return p;
    }
};

