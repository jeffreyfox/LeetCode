/*
A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list. 
*/

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */

/// Solution 1: use a hash table storing mapping from old to new nodes. Two passes.
/// First copy the array label/next fields and use a look-up table to store the mapping between old node and new node
/// Then deal with random array. Go through the old array and use the mapped new node link as the random field of new array.

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

/// Solution 2. still uses hash table, but one pass, deal with next and random pointers at the same time.

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        unordered_map<RandomListNode*, RandomListNode*> dict;
        RandomListNode* dummy = new RandomListNode(0);
        RandomListNode *p = head, *q = dummy;
        while(p) {
            if(dict.count(p) == 0) {
                q->next = dict[p] = new RandomListNode(p->label);
            } else q->next = dict[p];
            q = q->next;
            if(!p->random) q->random = NULL;
            else {
                if(dict.count(p->random) == 0) {
                    q->random = dict[p->random] = new RandomListNode(p->random->label);
                } else q->random = dict[p->random];
            }
            p = p->next; //move p to next
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

/// Solution 3. Very elegant. 3 passes with O(1) space (no hash table). The trick is to insert new nodes right after old node. Set random pointer, and then extract new array from the combined list.

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        RandomListNode *p = head, *q = NULL;
        //First pass, for each old node insert a new node after p
        while(p) {
            RandomListNode* tmp = p->next;
            p->next = new RandomListNode(p->label);
            p->next->next = tmp;
            p = tmp;
        }
        //Second pass, set random pointer
        p = head;
        while(p) {
            if(!p->random) p->next->random = NULL;
            else p->next->random = p->random->next;
            p = p->next->next;
        }
        //Third pass, extract new list from the combined list
        p = head; q = p->next;
        head = q; //new head to be returned
        while(p) {
            p->next = q->next;
            if(q->next) q->next = q->next->next;
            p = p->next;
            q = q->next;
        }
        return head;
    }
};

