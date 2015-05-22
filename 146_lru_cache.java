/// Use three data structures:
/// 1. table storing the <Key, Value> pair
/// 2. A doubly linked-list served as a FIFO queue. We put the newly accessed node to the tail, and pop the node at the head 
///    when cache is full
/// 3. A lookup table for the node address of each key, to avoid searching for the node in the list.

public class LRUCache {
    
    private HashMap<Integer, Integer> table; //table storing the key, value pair
    private HashMap<Integer, Node> lookup; //key's node reference in the list
    private Node head; //linked list head
    private Node tail; //linked list tail
    private int capacity; //capacity of cache
    private int N; //number of elements in the cache

    // doubly linked list node structure 
    private class Node {
        private int key;
        private Node prev;
        private Node next;
        public Node(int key) {
            this.key = key;            
        }
    }
    // constructor
    public LRUCache(int capacity) {
        table = new HashMap<Integer, Integer>();
        lookup = new HashMap<Integer, Node>();
        this.capacity = capacity;
        this.N = 0;
        this.head = null;
        this.tail = null;
    }
    // add a node to the tail of list
    private void addToTail(Node x) {
        x.prev = null;
        x.next = null;
        if (head == null) { //empty list
            head = x;
            tail = x;
        } else { //non empty list        
            tail.next = x;
            x.prev = tail;
            tail = x; //update tail!
        }
    }
    // delete a given node from list
    private void deleteFromList(Node x) {        
        if (x != head) x.prev.next = x.next;
        else head = x.next;
        if (x != tail) x.next.prev = x.prev;
        else tail = x.prev;
    }
    // get the key value
    // if not exist, return -1, do nothing with list
    // if exist, put the corresponding node to the tail of list
    public int get(int key) {
        Integer value = table.get(key);
        // not found value, return -1
        if (value == null) return -1;
        //found value, put node to end of list
        Node x = lookup.get(key);        
        deleteFromList(x);
        addToTail(x);

        return value;
    }
    // set the key value
    // if exist, then update value, put node to the tail of list
    // if not exist and cache not full, then add value to table and lookup, put the node to the tail of list
    // if not exist and cache full, then remove the head node (and delete entries in table and lookup), and add new value to table and lookup, and put the new node to the tail of list
    public void set(int key, int value) {
        if (table.containsKey(key)) { //already exist, put to tail
            Node x = lookup.get(key);
            deleteFromList(x);
            addToTail(x);
        } else if (N < capacity){ //not exist, and not full
            N++;
            Node x = new Node(key);
            addToTail(x); //insert to linked list
            lookup.put(key, x); //insert to lookup table
        } else { //full
            int oldkey = head.key;
            table.remove(oldkey);
            Node oldx = lookup.get(oldkey);
            deleteFromList(oldx);
            lookup.remove(oldkey);
            Node x = new Node(key);
            lookup.put(key, x); //insert to lookup table
            addToTail(x);
        }
        table.put(key, value); //update table
    }
}
