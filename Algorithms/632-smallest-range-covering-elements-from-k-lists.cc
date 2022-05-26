/*
You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.

 

Example 1:

Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
Example 2:

Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
Output: [1,1]
 

Constraints:

nums.length == k
1 <= k <= 3500
1 <= nums[i].length <= 50
-105 <= nums[i][j] <= 105
nums[i] is sorted in non-decreasing order.
*/

// The result has to start and end on a number in the list. 
// We can use k pointers. At the beginning, all the K pointers are at 0. We consider the min range that includes all the K numbers pointed by these K pointers.
// The min range is simply the min and max of these K numbers.
// Next step, we can remove the smallest number, and move the pointer one step forward. Then the min range that includes all these K numbers are again the min
// and max of these K numbers.
// So we essentially need to extract the minimum and maximum among the K numbers and also know the row and column indexes of the minimum number.
// For example:
// List 1: [4,10,15,24,26]
// List 2: [0,9,12,20]
// List 3: [5,18,22,30]
// Initially, we look at [4, 0, 5]. The minimum is 0 from the List 2's 1st element, the maximum is 5 and the min_range will be [0, 5] of size 5.
// Next, we remove the minimum element 0, and move the pointer forward, so we have [4, 9, 5], and the min_range will be [4, 9] of size 5.
// Since the order is non-decreasing, we don't need a priority queue to track the maximum, we can simply update it using the max function. But we do need a
// minimum-oriented priority queue to track the mininum entry as well as the indexes (to track the pointer position).
// When any of the pointers reaches beyond the end of the list, we don't need to scan further.
struct Record {
    int val;
    int row;
    int col;
    Record() : val(-1), row(-1), col(-1) {}
    Record(int v, int r, int c) : val(v), row(r), col(c) {}
};

class isGreater {
public:
    bool operator() (const Record &a, const Record &b) {
        return a.val > b.val;
    }
};

class Solution {
public:    
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<int> result;
        int min_range = INT_MAX;
        // mininum-oriented priority queue
        std::priority_queue<Record, std::vector<Record>, isGreater> pq;
        int maximum = INT_MIN;
        for (int r = 0; r < nums.size(); ++r) {
            pq.push(Record(nums[r][0], r, 0));
            maximum = max(maximum, nums[r][0]);
        }
        while (!pq.empty()) {
            int minimum = pq.top().val;
            int row = pq.top().row;
            int col = pq.top().col;
            pq.pop();
            if (maximum - minimum < min_range) {
                min_range = maximum - minimum;
                result = {minimum, maximum};
            }
            if (col == nums[row].size()-1) break;
            // Updates queue and the current maximum
            pq.push(Record(nums[row][col+1], row, col+1));
            maximum = max(maximum, nums[row][col+1]);
        }
        return result;
    }
};
