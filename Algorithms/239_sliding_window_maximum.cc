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

// Linear time (one pass) solution
// Maintain a doubly-ended queue. add newly seen numbers to end of queue. Several operations:
// 1. when we see a new number, pop all the smaller numbers from the back of queue, and then insert the new value. (the new number makes these smaller numbers values stale)
// 2. also check if front of queque is out of the sliding window, if yes then remove front.
// 3. the maximum is simply the front element of queue.

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
