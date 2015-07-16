/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// remove the node and shift the later nodes to front by 1
// time O(m) where m is the number of nodes after node
class Solution {
public:
    void deleteNode(ListNode* node) {
        while (1) {
            node->val = node->next->val;
            if (node->next->next == NULL) break;
            node = node->next;
        }
        delete node->next;
        node->next = NULL;
    }
};
