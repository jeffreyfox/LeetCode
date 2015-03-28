/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
// Divide and conquer solution
class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        int size = lists.size();
		if(size == 0) return NULL;
		while(size > 1) {
			for(int k = 0; k < size; k += 2) {
				if(k+1 < size) lists[k/2] = mergeTwoLists(lists[k], lists[k+1]);
				else lists[k/2] = lists[k];
			}
			size = (size+1)/2;
		}
		return lists[0];
    }
    
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)  {
		ListNode dum(0);
		ListNode *dummy(&dum);
		ListNode *tail = dummy;
		while(l1 && l2) {
			if(l1->val <= l2->val) { //append l1 to tail
				tail->next = l1;
				tail = l1;
				l1 = l1->next;
			} else { //append l2 to tail
				tail->next = l2;
				tail = l2;
				l2 = l2->next;
			}
		}
		//at this point either l1 or l2 is null
		if(l1) tail->next = l1;
		else if(l2) tail->next = l2;
		else tail->next = NULL;
		return dummy->next;
	}
};
