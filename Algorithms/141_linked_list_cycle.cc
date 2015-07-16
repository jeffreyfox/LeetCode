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
	bool hasCycle(ListNode *head) {
		ListNode *f(head), *s(head); //fast and slow pointer
		while(f && f->next) {
			s = s->next; 
			f = f->next; f = f->next; 
			if(f == s) return true;
		}
		return false;
	}
};
