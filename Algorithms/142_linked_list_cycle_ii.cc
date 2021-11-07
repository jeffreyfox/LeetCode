/*
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 2021. Use a hashtable to store the address of already visited nodes.
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head) return nullptr;
        unordered_set<ListNode*> dict;
        ListNode *curr = head;
        while (curr) {
            if (dict.count(curr)) return curr;
            dict.insert(curr);
            curr = curr->next;
        }
        return nullptr;
    }
};

// 2015.
// Floyd's algorithm. Maintain a slow and a fast pointer
// see http://keithschwarz.com/interesting/code/?dir=find-duplicate

class Solution {
public:
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
