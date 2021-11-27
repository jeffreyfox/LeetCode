/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10]. 
*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
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
