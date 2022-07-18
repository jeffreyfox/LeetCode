// Solution using a single condition variable. notify_all() is used.
// This is not optimized as a consumer thread may wake up other consumer threads (similarly for producer) causing spurious wake ups.
// A better solution is to use two CVs and let consumer only wake up producer and vice versa.

class BoundedBlockingQueue {
public:
    BoundedBlockingQueue(int capacity) {
        this->capacity = capacity;
    }
    
    void enqueue(int element) {
        unique_lock<mutex> ul(m);
        cv.wait(ul, [this](){ return q.size() < capacity;});
        q.push_back(element);
        cv.notify_all();
    }
    
    int dequeue() {
        unique_lock<mutex> ul(m);
        cv.wait(ul, [this](){ return q.size() > 0;});
        int v = q.front();
        q.pop_front();
        cv.notify_all();
        return v;
    }
    
    int size() {
        unique_lock<mutex> ul(m);
        return q.size();
    }
private:
    int capacity;
    deque<int> q;
    mutex m;
    condition_variable cv;
};

// An improved solution using two condition variables.
class BoundedBlockingQueue {
public:
    BoundedBlockingQueue(int capacity) {
        this->capacity = capacity;
    }
    
    void enqueue(int element) {
        unique_lock<mutex> ul(m);
        cv_full.wait(ul, [this](){ return q.size() < capacity;});
        q.push_back(element);
        cv_empty.notify_one();
    }
    
    int dequeue() {
        unique_lock<mutex> ul(m);
        cv_empty.wait(ul, [this](){ return q.size() > 0;});
        int v = q.front();
        q.pop_front();
        cv_full.notify_one();
        return v;
    }
    
    int size() {
        unique_lock<mutex> ul(m);
        return q.size();
    }
private:
    int capacity;
    deque<int> q;
    mutex m;
    condition_variable cv_full, cv_empty;
};
