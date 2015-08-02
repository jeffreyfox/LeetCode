/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// 3 steps:
// 1. Find middle element
// 2. reverse second half of array
// 3. compare second half with first half
/// O(n) time, O(1) space

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head == NULL || head->next == NULL) return true;
        ListNode *slow(head), *fast(head);
        // find the middle element or end of first half segment
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        //move one step further
        slow = slow->next;
        //reverse second half segment
        ListNode *newhead = reverseList(slow);
        //compare second half with first half
        while (newhead) {
            if (newhead->val != head->val) return false;
            head = head->next;
            newhead = newhead->next;
        }
        return true;
    }
    ListNode* reverseList(ListNode *head) {
        ListNode *curr(head), *next(head->next), *nextnext(NULL);
        while (next) {
            nextnext = next->next;
            next->next = curr;
            curr = next;
            next = nextnext;
        }
        head->next = NULL; //need to seet tail as NULL!
        return curr;
    }
};
