/*
Given a linked list, determine if it has a cycle in it.

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
    bool hasCycle(ListNode *head) {
        if (!head) return false;
        unordered_set<ListNode*> dict;
        while (head) {
            if (dict.count(head)) return true;
            dict.insert(head);
            head = head->next;
        }
        return false;
    }
};

// 2015.
// Floyd's algorithm. Maintain a slow and a fast pointer
// see http://keithschwarz.com/interesting/code/?dir=find-duplicate

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == NULL) return false;
        ListNode *slow(head), *fast(head);
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) return true;
        }
        return false;
    }
};
