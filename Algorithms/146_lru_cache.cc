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
        auto iter = key_to_list.find(key);
        if (iter == key_to_list.end()) {
            return -1;
        }
        DLLNode *node = iter->second;
        remove(node);
        push_back(node);
        return node->value;
    }
    
    void put(int key, int value) {        
        auto iter = key_to_list.find(key);
        if (iter != key_to_list.end()) {
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
            key_to_list[key] = new_node;
            N++;
            // If reaching capacity, remove the LRU element from cache and list
            if (N > maxN) {
                DLLNode *old_node = head->next;
                key_to_list.erase(old_node->key);
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
    unordered_map<int, DLLNode*> key_to_list;
    DLLNode *head;  // dummy head
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// Same idea using std::list.
// Use std::prev to point to the last element.
// std::list does not expose a way to move an element to the end. So we first delete and then push back a new one. This means we need to update the hashtable (whereas in the
// previous implementation the same node is moved to the end of list.

class LRUCache {
public:
    // Uses a double-linked list for O(1) deletion
    struct Record {
        int key;
        int value;
        Record(int k, int v) : key(k), value(v) {}
    };
    
    LRUCache(int capacity) {
        N = 0;
        maxN = capacity;        
    }
    
    int get(int key) {
        auto iter = dict.find(key);
        if (iter == dict.end()) {
            return -1;
        }
        auto list_iterator = iter->second;
        auto record = *list_iterator;
        records.erase(list_iterator);
        records.push_back(record);
        dict[key] = prev(records.end(), 1);
        return record.value;
    }
    
    void put(int key, int value) {        
        auto iter = dict.find(key);
        if (iter != dict.end()) {
            // key already exists, updates value and move to the end of the list
            auto list_iterator = iter->second;
            list_iterator->value = value;   
            // Move the node to the end of the list
            auto record = *list_iterator;
            records.erase(list_iterator);
            records.push_back(record);
            dict[key] = prev(records.end(), 1);
        } else {
            // key does not exist, create a record in hashtable and add it to the end of the list
            records.push_back(Record(key, value));
            dict[key] = prev(records.end(), 1);
            N++;
            // If reaching capacity, remove the LRU element from cache and list
            if (N > maxN) {                
                dict.erase(records.begin()->key);
                records.erase(records.begin());
                N--;
            }
        }
    }

private:
    int maxN;  // capacity of the cache
    int N;  // number of keys in the cache
    unordered_map<int, list<Record>::iterator> dict;
    list<Record> records;
};

class LRUCache{

public:
    struct ListNode {
        ListNode *prev, *next;
        int key, val;
        ListNode(int k, int v) : key(k), val(v), prev(NULL), next(NULL) {}
    };

    LRUCache(int capacity) {
        this->capacity = capacity;
        this->N = 0;
        //dummy head and tail
        head = new ListNode(-1, 0);
        tail = new ListNode(-1, 0);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        ListNode *node = head;
        while(node) {
            ListNode* tmp = node;
            node = node->next;
            delete tmp;
        }
    }

    int get(int key) {
        if(dict.count(key)) {
            ListNode* node = dict[key];
            removeFromList(node);
            appendToList(node);
            return node->val;
        } else return -1;       
    }
    
    void set(int key, int value) {
        if(dict.count(key)) { //found, just update
            ListNode* node = dict[key];
            node->val = value;
            removeFromList(node);
            appendToList(node);
        } else { //not found, insert
            ListNode *node = new ListNode(key, value);
            dict[key] = node;
            appendToList(node);
            N++;
            if(N > capacity) {
               node = head->next;
               removeFromList(node);
               dict.erase(node->key); //erase entry from map
               delete node;
               N--;
            }
        }
    }

private:
    void removeFromList(ListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void appendToList(ListNode* node) {
        node->prev = tail->prev;
        node->next = tail;
        tail->prev->next = node;
        tail->prev = node;
    }
    int capacity;
    int N;
    unordered_map<int, ListNode*> dict;
    ListNode *head, *tail;
};

