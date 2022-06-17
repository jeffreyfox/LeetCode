/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item. 
*/

/*
 Use a double-linked list, and use a dummy head and tail.
 Maintain a count of elements and capiticy.
 When an element has been touched, move to end of list
 When inserting a new element, first check if reaching maximum capacity. If yes, first delete head element. Then append new element to tail.
 Also included proper delete functions when nodes are removed and in the destructor.
 Uses a dummy head (dummy tail is not needed)
*/
class LRUCache {
public:
    // Uses a double-linked list for O(1) deletion
    struct DLLNode {
        DLLNode *prev;
        DLLNode *next;
        int key;
        int value;
        DLLNode() : prev(nullptr), next(nullptr), key(-1), value(-1) {}
        DLLNode(int k, int v) : prev(nullptr), next(nullptr), key(k), value(v) {} 
    };
    
    LRUCache(int capacity) {
        N = 0;
        maxN = capacity;
        head = new DLLNode();
        head->next = head;
        head->prev = head;
    }
    
    int get(int key) {
        auto iter = key_to_node.find(key);
        if (iter == key_to_node.end()) {
            return -1;
        }
        DLLNode *node = iter->second;
        remove(node);
        push_back(node);
        return node->value;
    }
    
    void put(int key, int value) {        
        auto iter = key_to_node.find(key);
        if (iter != key_to_node.end()) {
            // key already exists, updates value and move to the end of the list
            auto *node = iter->second;            
            node->value = value;            
            // Move the node to the end of the list
            remove(node);
            push_back(node);
        } else {
            // key does not exist, create a record in hashtable and add it to the end of the list
            DLLNode *new_node = new DLLNode(key, value);
            push_back(new_node);
            key_to_node[key] = new_node;
            N++;
            // If reaching capacity, remove the LRU element from cache and list
            if (N > maxN) {
                DLLNode *old_node = head->next;
                key_to_node.erase(old_node->key);
                remove(old_node);
                delete old_node;
                N--;
            }
        }
    }
    // Remove node from the list.
    void remove(DLLNode *node) {
        DLLNode *prev = node->prev;
        DLLNode *next = node->next;
        prev->next = next;
        next->prev = prev;
    }
    // Add node to the tail of the list
    void push_back(DLLNode *node) {
        auto *tail = head->prev;
        tail->next = node;        
        node->prev = tail;
        node->next = head;
        head->prev = node;
    }

private:
    int maxN;  // capacity of the cache
    int N;  // number of keys in the cache
    unordered_map<int, DLLNode*> key_to_node;
    DLLNode *head;  // dummy head
};

// Same idea using std::list.
// Use list::splice to move an element from middle of the list to the end of the list.
class LRUCache {
public:
    struct Record {
        int key;
        int value;
        Record(int k, int v) : key(k), value(v) {}
    };

    LRUCache(int capacity) {
        cap = capacity;
        count = 0;
    }
    
    int get(int key) {
        if (!dict.count(key)) return -1;
        auto curr = dict[key];
        // Move to the end of the list
        dll.splice(dll.end(), dll, curr);
        return curr->value;
    }
    
    void put(int key, int value) {
        if (dict.count(key)) {
            auto curr = dict[key];
            curr->value = value;
            dll.splice(dll.end(), dll, curr);
        } else {
            // new element, insert to tail
            dll.push_back(Record(key, value));
            dict[key] = std::next(dll.end(), -1);
            count ++;
        }
        if (count > cap) {
            dict.erase(dll.begin()->key);
            dll.pop_front();
            count--;
        }
    }
    
private:
    int cap;
    int count;
    list<Record> dll;
    unordered_map<int, list<Record>::iterator> dict;    
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
