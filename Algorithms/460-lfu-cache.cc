// Solution using nested lists and two hash maps.
// The nested list looks like follows:
// element #1 (for count = 1): (k: 1, v: 1, c: 1) -> (k: 2, v: 2, c: 1) -> ...
// element #2 (for count = 3): (k: 3, v: 3, c: 3)
// Each outer list element is a list corresponding to the frequency bucket.
// Each inner list element is the actual key-value node with the frequency count.
// Each time we update the count of an inner list element, we need to move it from the old outer list to the tail of the next outer list.
// We need to properly create or delete empty outer lists if needed.

class LFUCache {
public:
    struct Record {
        int key;
        int value;
        int count;
        Record(int k, int v, int c) : key(k), value(v), count(c) {}
    };
    
    LFUCache(int capacity) {
        cap = capacity; num_records = 0;
    }
       
    int get(int key) {
        if (!key2record.count(key)) return -1;
        auto curr = key2record[key];
        curr->count++;
        update(curr);
        return curr->value;
    }
    
    void put(int key, int value) {
        // To handle corner case
        if (cap == 0) return;

        if (key2record.count(key)) {
            auto curr = key2record[key];
            curr->value = value;
            curr->count++;
            update(curr);
        } else {
            // new element, insert to tail of bucket of size 1. Before insertion, remove LFU if reaching capacity.
            if (num_records == cap) {
                auto &bucket = *buckets.begin();
                int key_to_delete = bucket.begin()->key;
                int count = bucket.begin()->count;
                key2record.erase(key_to_delete);
                bucket.pop_front();
                if (bucket.empty()) {
                    count2bucket.erase(count);
                    buckets.pop_front();
                }
                num_records--;
            }      
            
            if (!count2bucket.count(1)) {
                buckets.push_front({});
                count2bucket[1] = buckets.begin();
            }
            auto bucket = count2bucket[1];
            bucket->push_back(Record(key, value, 1));
            key2record[key] = std::prev(bucket->end());
            num_records ++;
        }
    }

private:
    // A helper function to move the node to the end of the next bucket (e.g. if current count is 2, we need to remove it from bucket 1 and move to end of bucket 2).
    // Needs to remove current bucket (1) if it becomes empty.
    // Also needs to create a new bucket for the new count (2) if it doesn't exist.
    void update(list<Record>::iterator curr) {
        list<list<Record>>::iterator old_bucket = count2bucket[curr->count-1];
        if (!count2bucket.count(curr->count)) {
            count2bucket[curr->count] = buckets.insert(std::next(old_bucket), list<Record>());
        }
        list<list<Record>>::iterator new_bucket = count2bucket[curr->count];
        new_bucket->splice(new_bucket->end(), *old_bucket, curr);
        if (old_bucket->empty()) {
            count2bucket.erase(curr->count-1);
            buckets.erase(old_bucket);            
        }
    }
    int cap;
    int num_records;
    list<list<Record>> buckets;
    unordered_map<int, list<Record>::iterator> key2record;
    unordered_map<int, list<list<Record>>::iterator> count2bucket;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
