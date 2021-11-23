/*
Design a HashSet without using any built-in hash table libraries.

Implement MyHashSet class:

void add(key) Inserts the value key into the HashSet.
bool contains(key) Returns whether the value key exists in the HashSet or not.
void remove(key) Removes the value key in the HashSet. If key does not exist in the HashSet, do nothing.
 

Example 1:

Input
["MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"]
[[], [1], [2], [1], [3], [2], [2], [2], [2]]
Output
[null, null, null, true, false, null, true, null, false]

Explanation
MyHashSet myHashSet = new MyHashSet();
myHashSet.add(1);      // set = [1]
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(1); // return True
myHashSet.contains(3); // return False, (not found)
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(2); // return True
myHashSet.remove(2);   // set = [1]
myHashSet.contains(2); // return False, (already removed)
 

Constraints:

0 <= key <= 106
At most 104 calls will be made to add, remove, and contains.
*/

// Uses a vector and single linked list to store the values. Amortizes O(1)??
class MyHashSet {
public:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(-1), next(nullptr) {}
        ListNode(int v) : val(v), next(nullptr) {}
    };

    // Should also have a dtor to clear the nodes.
    MyHashSet() : n(100) {        
        buckets.resize(n);
        for (int k = 0; k < n; ++k) {
            // dummy head
            buckets[k] = new ListNode();
        }
    }    
    
    void add(int key) {
        if (contains(key)) return;
        int k = key % n;        
        ListNode *p = new ListNode(key);
        p->next = buckets[k]->next;
        buckets[k]->next = p;
    }
    
    void remove(int key) {
        // Find the node along with its parent
        int k = key % n;
        ListNode *prev = buckets[k], *curr = prev->next;
        while (curr) {
            if (curr->val == key) {
                // delete the node
                prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr; curr = curr->next;
        }
    }
    
    bool contains(int key) {
        int k = key % n;
        ListNode *node = buckets[k]->next;
        while (node) {
            if (node->val == key) return true;
            node = node->next;
        }
        return false;
    }
    
private:
    vector<ListNode*> buckets;
    const int n;  // number of buckets
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
