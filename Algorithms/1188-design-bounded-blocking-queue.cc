class BoundedBlockingQueue {
private:
    int N;
    int sz;
    mutex m;
    condition_variable cv;
    deque<int> arr;

public:
    BoundedBlockingQueue(int capacity) {
        N = capacity;
        sz = 0;
    }
    
    void enqueue(int element) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this]{return sz < N;});
        arr.push_front(element);
        sz++;
        cv.notify_all();
    }
    
    int dequeue() {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this]{return sz > 0;});
        int result = arr.back();
        arr.pop_back();
        sz--;
        cv.notify_all();
        return result;
    }
    
    int size() {
        return sz;
    }
};
