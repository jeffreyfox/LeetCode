/*
 Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item. 
*/

/// Use a double-linked list, and use a dummy head and tail.
/// Maintain a count of elements and capiticy.
/// When an element has been touched, move to end of list
/// When inserting a new element, first check if reaching maximum capacity. If yes, first delete head element. Then append new element to tail.

class LRUCache 	{
public:
    struct ListNode {
        int key, value; //key and value
        ListNode *prev, *next;
        ListNode(int k, int v): key(k), value(v), prev(NULL), next(NULL) {}
    };

    LRUCache(int capacity) {
       head = new ListNode(-1, -1);
       tail = new ListNode(-1, -1);
       head->next = tail;
       tail->prev = head;
       this->capacity = capacity;
       count = 0;
    }

    ~LRUCache() {
        ListNode *node = head;
        while(node) {
            ListNode *tmp = node;
            node = node->next;
            delete tmp;
        }
    }

    int get(int key) {
        map<int, ListNode*>::iterator it = st.find(key);
        if(it == st.end()) return -1;
        moveToTail(it->second);
        return it->second->value;
    }

    void set(int key, int value) {
        map<int, ListNode*>::iterator it = st.find(key);
        if (it == st.end()) { // not exist, add
            if(count == capacity) {
               deleteHead();
               count--;
            }
            ListNode *newnode = new ListNode(key, value);
            appendToTail(newnode);
            st[key] = newnode;
            count++;
        } else { //already exist, put to tail and update
            moveToTail(it->second);
            it->second->value = value;
        }
    }

    map<int, ListNode*> st; //symbol table
    ListNode *head, *tail; //dummy head and tail
    int count, capacity;

    void moveToTail(ListNode* node) {
        if(node->next == tail) return; //no need to touch if already at tail
        //first delete from middle
        node->prev->next = node->next;
        node->next->prev = node->prev;
        //then append to tail
        appendToTail(node);
    }
    void appendToTail(ListNode* node) {
        node->prev = tail->prev;
        node->next = tail;
        node->prev->next = node;
        node->next->prev = node;
    }
    void deleteHead() {
        ListNode *tmp = head->next;
        st.erase(tmp->key);
        head->next = tmp->next;
        tmp->next->prev = head;
        delete tmp;
    }
};
