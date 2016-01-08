/*
Sort a linked list in O(n log n) time using constant space complexity.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution 1. Top-down merge sort (not really constant space, because of stack space)
// when finding the middle element, fast is initialized as head->next, not head, to avoid infinite loop in corner cases (only two nodes).

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* p = head, *q = head;
        while(q->next && q->next->next) {
            p = p->next;
            q = q->next->next;
        }
        //merge head and p->next
        q = p->next;
        p->next = NULL;
        head = sortList(head);
        q = sortList(q);
        return merge(head, q);
    }

    ListNode *merge(ListNode* left, ListNode *right) {
        ListNode* dummy = new ListNode(0);
        ListNode *p = left, *q = right, *tail = dummy;
        while(p && q) {
            if(p->val <= q->val) {
                tail->next = p; p = p->next;
            } else {
                tail->next = q; q = q->next;
            }
            tail = tail->next;
        }
        tail->next = p ? p : q;

        p = dummy->next;
        delete dummy;
        return p;
    }
};

// Solution 2. Bottom-up merge sort with O(1) space, by using an elegant split function.
// Maintain the length of sub lists to be sorted, starting form 1, and then 2, 4 ...
// Split(head, len), cuts break the list at position len, and returns the head of the second part, e.g.
// head = 1 -> 2 -> 3 -> 4, len = 2, then after second = split(head, 2), we have head = 1->2,  second = 3->4.
// Merge merges to linked lists and attach them to the head, and then returns the tail of the merged list.

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        int count = 0;
        ListNode *p = dummy->next;
        while(p) {
            count++;
            p = p->next;
        }
        for(int len = 1; len < count; len *= 2) { //len: merge length
            ListNode *tail = dummy, *left = dummy->next;
            while(left) {
                ListNode *right = split(left, len);
                ListNode *next = split(right, len);
                tail = merge(left, right, tail);
                left = next;
            }
        }
        head = dummy->next;
        delete dummy;
        return head;
    }

    ListNode* split(ListNode *head, int len) {
        while(head && len > 1) {
           head = head->next; len--;
        }
        if(!head) return NULL;
        ListNode *second = head->next;
        head->next = NULL;
        return second;
    }
    //merge two lists and attach to head (head serves similar to the dummy head), and return the tail of the merged list
    ListNode *merge(ListNode* left, ListNode *right, ListNode *head) {
        ListNode *p = left, *q = right, *tail = head;
        while(p && q) {
            if(p->val < q->val) {
                tail->next = p; p = p->next;
            } else {
                tail->next = q; q = q->next;
            }
            tail = tail->next;
        }
        tail->next = p ? p : q;
        while(tail->next) tail = tail->next;
        return tail;
    }
};

// Solution 3. 3-way quick-sort, with the first element as the pivot. Maintain three sub lists, one < x, one == x, one > x. Then attach them ogether in the end. Not really O(1) space, due to recursive calls.

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
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        return sortList(head, NULL);
    }
    //sort list and connect it to next, return new head
    ListNode* sortList(ListNode *head, ListNode *next) {
        ListNode* dummy = new ListNode(0);
        //use head as pivot. p : <x, q : >x, r : =x
        ListNode *phead = NULL, *qhead = NULL, *rhead = NULL;
        ListNode *p = NULL, *q = NULL, *r = head;
        ListNode *curr = head->next;
        while(curr) {
            if(curr->val < head->val) {
                if(!p) p = phead = curr;
                else p = p->next = curr;
            } else if(curr->val > head->val) {
                if(!q) q = qhead = curr;
                else q = q->next = curr;
            } else {
                r = r->next = curr;
            }
            curr = curr->next;
        }
        //work on first part (<x)
        if(phead) {
            p->next = NULL; //p is tail
            dummy->next = sortList(phead, head);
        } else dummy->next = head;
        //work on second part (>x)
        if(qhead) {
            q->next = NULL; //q is tail
            r->next = sortList(qhead, next);
        } else r->next = next;
        head = dummy->next;
        delete dummy;
        return head;
    }
};

// Solution 4. Bottom-up merge sort, using a queue. O(n) space!
// Sort is unstable if number of nodes are not power of 2!

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        deque<ListNode*> q;
        ListNode *p = head;
        //push nodes into queue, also set next to NULL (break into many single-node lists)
        while(p) {
            q.push_back(p);
            ListNode *next = p->next;
            p->next = NULL;
            p = next;
        }
        ListNode dum(0);
        p = &dum; //dummy node
        while(!q.empty()) {
            ListNode* n1 = q.front(); q.pop_front();
            if(q.empty()) return n1;
            ListNode *n2 = q.front(); q.pop_front();
            q.push_back(merge(n1, n2));
        }
        return NULL; //something wrong
    }
    //merge two sorted, non-empty lists
    ListNode* merge(ListNode *head1, ListNode *head2) {
        ListNode dum(0), *p(&dum), *tail(p);
        while(head1 && head2) {
            if(head1->val <= head2->val) {
                tail->next = head1;
                head1 = head1->next;
            } else {
                tail->next = head2;
                head2 = head2->next;
            }
            tail = tail->next;
        }
        tail->next = head1 ? head1 : head2;
        return p->next;
    }
};

