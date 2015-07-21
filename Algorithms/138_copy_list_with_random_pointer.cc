/// First copy the array label/next fields and use a look-up table to store the mapping between old node and new node
/// Then deal with random array. Go through the old array and use the mapped new node link as the random field of new array.
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(head == NULL) return head;
        RandomListNode *newhead = new RandomListNode(head->label);
        RandomListNode *p = head, *q = newhead;
        map<RandomListNode*, RandomListNode*> lookup;
        lookup[p] = q;
        while (p->next) {
            q->next = new RandomListNode(p->next->label);
            lookup[p->next] = q->next;
            p = p->next;
            q = q->next;
        }
        
        //now deal with the random pointer
        p = head;
        q = newhead;
        while(p) {
            q->random = lookup[p->random];
            p = p->next;
            q = q->next;
        }
        return newhead;
    }
};
