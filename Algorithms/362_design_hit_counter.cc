Design a hit counter which counts the number of hits received in the past 5 minutes (i.e., the past 300 seconds).

Your system should accept a timestamp parameter (in seconds granularity), and you may assume that calls are being made to the system in chronological order (i.e., timestamp is monotonically increasing). Several hits may arrive roughly at the same time.

/*
Implement the HitCounter class:

HitCounter() Initializes the object of the hit counter system.
void hit(int timestamp) Records a hit that happened at timestamp (in seconds). Several hits may happen at the same timestamp.
int getHits(int timestamp) Returns the number of hits in the past 5 minutes from timestamp (i.e., the past 300 seconds).
 

Example 1:

Input
["HitCounter", "hit", "hit", "hit", "getHits", "hit", "getHits", "getHits"]
[[], [1], [2], [3], [4], [300], [300], [301]]
Output
[null, null, null, null, 3, null, 4, 3]

Explanation
HitCounter hitCounter = new HitCounter();
hitCounter.hit(1);       // hit at timestamp 1.
hitCounter.hit(2);       // hit at timestamp 2.
hitCounter.hit(3);       // hit at timestamp 3.
hitCounter.getHits(4);   // get hits at timestamp 4, return 3.
hitCounter.hit(300);     // hit at timestamp 300.
hitCounter.getHits(300); // get hits at timestamp 300, return 4.
hitCounter.getHits(301); // get hits at timestamp 301, return 3.
 

Constraints:

1 <= timestamp <= 2 * 109
All the calls are being made to the system in chronological order (i.e., timestamp is monotonically increasing).
At most 300 calls will be made to hit and getHits.
 

Follow up: What if the number of hits per second could be huge? Does your design scale?
*/
 
// Maintain a deque to store the number of counts for a given timestamp. Cleanup when earlier records are more than 5 min old.
class HitCounter {
public:
    struct Record {
        int timestamp;
        int count;
        Record() : timestamp(0), count(0) {}
        Record(int ts, int c) : timestamp(ts), count(c) {}
    };

    HitCounter() {
        
    }
    
    void hit(int timestamp) {
        if (!q.empty() && q.back().timestamp == timestamp) {
            q.back().count++;
        } else {
            q.push_back(Record(timestamp, 1));
        }
        
        while (!q.empty()) {
            if (q.front().timestamp <= timestamp - 300) q.pop_front();
            else break;
        }
    }
    
    int getHits(int timestamp) {
        int count = 0;
        for (auto r = q.rbegin(); r != q.rend(); ++r) {
            if (r->timestamp > timestamp - 300) count += r->count;
            else break;
        }
        return count;
    }
private:
    deque<Record> q;
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */  
