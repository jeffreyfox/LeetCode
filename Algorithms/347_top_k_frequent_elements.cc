/*
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:

Input: nums = [1], k = 1
Output: [1]

Constraints:

    1 <= nums.length <= 105
    k is in the range [1, the number of unique elements in the array].
    It is guaranteed that the answer is unique.

Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/

// Uses a priority queue with a customized comparator supplied by a lambda function.
class Solution {
public:
    // Record stores the integer value and its count (frequency).
    struct Record {
        int value;
        int count;
        Record() : value(0), count(0) {}
        Record(int v, int c) : value(v), count(c) {}
    };

    vector<int> topKFrequent(vector<int>& nums, int k) {
        std::map<int, int> freq;
        for (const auto val : nums) {
            freq[val] ++;
        }
        // Customized comparator supplied by a lambda function.
        auto compare = [](Record a, Record b) { return a.count < b.count;};
        std::priority_queue<Record, std::vector<Record>, decltype(compare)> pq(compare);
        // Build the heap
        for (const auto &[value, count] : freq) {
            pq.push(Record(value, count));
        }
        // Return the top k results.
        vector<int> result;
        result.reserve(k);
        for (int i = 0; i < k; ++i) {
            result.push_back(pq.top().value);
            pq.pop();
        }
        return result;
    }
};
