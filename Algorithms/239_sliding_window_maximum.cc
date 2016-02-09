/*
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.
*/

// Solution 1. Linear time (one pass) solution
// Maintain a doubly-ended queue. add newly seen numbers to end of queue. Several operations:
// 1. when we see a new number, pop all the smaller numbers from the back of queue, and then insert the new value (the new number makes these smaller numbers values stale).
// 2. also check if front of queque is out of the sliding window, if yes then remove front.
// 3. the maximum is simply the front element of queue.
// This method has time complexity of amortized O(1) per element, and worst case O(n) per element. Space complexity is O(k) (not counting result vector).

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        int n = nums.size();
        if(n == 0 || k == 0 || n < k) return result;
        result.resize(n-k+1);
        deque<int> q; //position
        for(int i = 0; i < n; ++i) {
            int val = nums[i];
            if(!q.empty() && i-q.front() == k) q.pop_front();
            while(!q.empty() && nums[q.back()] <= val) {
                q.pop_back();
            }
            q.push_back(i);
            if(i >= k-1) result[i-k+1] = nums[q.front()];
        }
        return result;
    }
};

// Solution 2 using an indexed priority queue. Think of the input as a vector of size k. Each time window moves forward, a number in it
// gets updated. The PQ maintains three vectors:
// nums: values as key for sorting,
// pq: pq[i] stores the index in input vector for the i-th element in PQ (1-based)
// qp: qp[i] stores the index in PQ for the i-th element in input vector (1-based)
// properly update the vectors when doing swapping.

class IndexedPQ {
public:
    IndexedPQ(int cap) : capacity(cap), N(0) {
        pq.resize(cap+1, 0);
        qp.resize(cap+1, 0);
        nums.resize(cap+1, 0);
    }
    IndexedPQ(vector<int>::iterator beg, vector<int>::iterator end) {
        N = end-beg;
        capacity = N+1;
        pq.resize(capacity, 0);
        qp.resize(capacity, 0);
        nums.resize(capacity, 0);
        for(int i = 1; i <= N; i++) {
            pq[i] = qp[i] = i;
            nums[i] = *(beg + (i-1));
        }
        for(int i = N/2; i >= 1; i--) fixDown(i);
    }
    //insert key with index i in input vector (1-based)
    void insert(int i, int key) {
        N++;
        pq[N] = i; //index in pq => index in input
        qp[i] = N;
        nums[N] = key;
        fixUp(N);
    }
    //update value associated with input index i 
    void update(int i, int key) {
        int k = qp[i]; //index in heap
        int old_key = nums[k];
        nums[k] = key;
        if(old_key < key) fixUp(k);
        else if(old_key > key) fixDown(k);
    }
    int extractMin() {
        return nums[1];
    }
    bool empty() { return N == 0; }

private:
    void fixUp(int k) {
        while(k > 1 && nums[k/2] < nums[k]) {
            swap(k, k/2);
            k /= 2;
        }
    }
    void fixDown(int k) {
        while(2*k <= N) {
            int j = 2*k;
            if(j < N && nums[j+1] > nums[j]) j++;
            if(nums[j] <= nums[k]) break;
            swap(j, k);
            k = j;
        }
    }
    //swap two elements with indices in pq
    void swap(int i, int j) {
        int t = 0;
        t = qp[pq[i]]; qp[pq[i]] = qp[pq[j]]; qp[pq[j]] = t;
        t = pq[i]; pq[i] = pq[j]; pq[j] = t;
        t = nums[i]; nums[i] = nums[j]; nums[j] = t;
    }
    int N; //number of elements
    int capacity; //capacity
    vector<int> pq; //index in PQ => index in input array
    vector<int> qp; //index in input array => index in PQ
    vector<int> nums; //keys (actual values)
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        int n = nums.size();
        if(nums.empty() || n < k || k <= 0) return result;
        IndexedPQ q(nums.begin(), nums.begin()+k);
        result.push_back(q.extractMin());
        for(int i = k; i < n; i++) {
            int idx = (i-k) % k + 1;
            q.update(idx, nums[i]);
            result.push_back(q.extractMin());
        }
        return result;        
    }
};

// Solution 3. A O(k*n) solution.
// For each new number, look further and predict the maximum for the next k steps

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
       int n = nums.size();
       vector<int> ret;
       if(k == 0 || n < k) return ret;
       int m = n-k+1;
       ret.resize(m, INT_MIN);
       //predict the possible maximums according to nums[i]
       for(int i = 0; i < n; ++i) {
          for(int j = max(0, i-k+1); j <= min(i, m-1); ++j) {
             ret[j] = max(ret[j], nums[i]);
          }
       }
       return ret;
    }
};

