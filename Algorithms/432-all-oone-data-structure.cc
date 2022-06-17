// Solution 1. Use std::list which is a doubly linked list. It is tricky when removing and adding an element to a position.
class AllOne {
public:
    struct Record {
        string key;
        int val;
        Record(const string& k, int v) : key(k), val(v) {}
    };

    AllOne() {      
    }
    
    void inc(string key) {
        if (!dict.count(key)) {
            // First time, insert at beginning
            dll.push_front(Record(key, 1));
            dict[key] = dll.begin();            
        } else {
            auto curr = dict[key];
            curr->val++;
            // Find the first element whose value >= current value
            auto iter = std::next(curr, 1);
            while (iter != dll.end() && iter->val < curr->val) iter++;
            if (iter != std::next(curr, 1)) {
                // insert before iter (remove and insert a new one)
                Record record(*curr);
                dll.erase(curr);
                // Needs to update dict
                dict[key] = dll.insert(iter, record);                
            }
        }        
    }
    
    void dec(string key) {
        auto curr = dict[key];
        curr->val--;
        if (curr->val == 0) {
            dict.erase(key);
            dll.erase(curr);
        } else {
            // find the first element whose value <= current value
            auto iter = std::next(curr, -1);
            while (iter != std::next(dll.begin(), -1) && iter->val > curr->val) iter--;
            if (iter != std::next(curr, -1)) {
                // insert after iter (remove and insert a new one)
                Record record(*curr);
                dll.erase(curr);                
                ++iter;
                // Needs to update dict.
                dict[key] = dll.insert(iter, record);
            }
        }
    }
    
    string getMaxKey() {
        return dll.empty() ? "" : dll.back().key;
    }
    
    string getMinKey() {
        return dll.empty() ? "" : dll.front().key;
    }

private:
    list<Record> dll;
    unordered_map<string, list<Record>::iterator> dict;
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */

// Solution 2.
// Use a doubly linked list and a hash map.
// Use a dummy head, which complicates the process of finding the new insertion point.

class AllOne {
public:
    struct DllNode {
        string key;
        int val;
        DllNode *prev, *next;
        DllNode(const string& k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
    };

    AllOne() {
        head = new DllNode("", -1);
        head->next = head;
        head->prev = head;
    }
    
    void inc(string key) {
        if (!dict.count(key)) {
            DllNode *node = new DllNode(key, 1);
            dict[key] = node;
            // insert after head
            insert(head, node);            
        } else {
            DllNode *node = dict[key];
            node->val++;
            DllNode *p = node;
            while (p->next != head && p->next->val < node->val) p = p->next;
            if (p != node) {
                // insert after p
                remove(node);
                insert(p, node);
            }
        }        
    }
    
    void dec(string key) {
        DllNode* node = dict[key];
        --node->val;
        if (node->val == 0) {
            dict.erase(key);
            remove(node);
        } else {
            // find the previous node to link after
            DllNode *p = node;
            while (p->prev != head && p->prev->val > node->val) p = p->prev;
            if (p != node) {
                // insert after p->prev
                remove(node);
                insert(p->prev, node);
            }
        }
    }
    
    string getMaxKey() {
        return head->prev->key;
    }
    
    string getMinKey() {
        return head->next->key;
    }
private:
    void insert(DllNode* prev, DllNode *node) {        
        node->next = prev->next;
        node->prev = prev;        
        prev->next->prev = node;
        prev->next = node;
    }
    void remove(DllNode *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    DllNode *head;
    unordered_map<string, DllNode*> dict;
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
