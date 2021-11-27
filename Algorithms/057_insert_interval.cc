/*
You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.

Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).

Return intervals after the insertion.

 

Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
Example 3:

Input: intervals = [], newInterval = [5,7]
Output: [[5,7]]
Example 4:

Input: intervals = [[1,5]], newInterval = [2,3]
Output: [[1,5]]
Example 5:

Input: intervals = [[1,5]], newInterval = [2,7]
Output: [[1,7]]
 

Constraints:

0 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 105
intervals is sorted by starti in ascending order.
newInterval.length == 2
0 <= start <= end <= 105
 */

/// scan intervals from left to right:
// 1. if current interval overlaps with newInterval, then merge the two and update newInterval
// 2. if not overlap, then push-back the one with smaller start time to final array, and make the other one as newInterval.
// Use a flag "new_inserted" to check if newInterval already inserted. If yes, then no need to perform interval comparison in later step (just copy and paste)

bool isOverlap(const vector<int> &a, const vector<int>& b) {
    return a[1] >= b[0] && b[1] >= a[0];
}

vector<int> merge(const vector<int> &a, const vector<int>& b) {
    return {min(a[0], b[0]), max(a[1], b[1])};
}

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        bool new_inserted = false;
        for (const auto& interval : intervals) {
            if (new_inserted) result.push_back(interval);
            else if (isOverlap(interval, newInterval)) {
                newInterval = merge(interval, newInterval);
            } else {
                if (newInterval[0] < interval[0]) { // new goes before the current one
                    result.push_back(newInterval);
                    result.push_back(interval);
                    new_inserted = true;                    
                } else { // new goes after the current one
                    result.push_back(interval);
                }                    
            }
        }
        if (!new_inserted) result.push_back(newInterval);
        return result;
    }
};
