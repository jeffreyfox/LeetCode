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
// Use a tag "inserted" to check if newInterval already inserted. If yes, then no need to perform interval comparison in later step (just copy and paste)

class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> result;
        if(intervals.empty()) {
            result.push_back(newInterval);
            return result;
        }
        int n = intervals.size();
        bool inserted = false;
        for(int i = 0; i < n; ++i) {
           const Interval& current = intervals[i];
           if(inserted) result.push_back(current);
           else if(newInterval.start <= current.end && current.start <= newInterval.end) { //merge the two
               newInterval.start = min(current.start, newInterval.start);
               newInterval.end = max(current.end, newInterval.end);
           } else { //not overlap
               if(current.start > newInterval.start) {
                   result.push_back(newInterval); //smaller start goes first
                   result.push_back(current);
                   inserted = true; //finshed insertion
               } else {
                   result.push_back(current); //smaller start goes first
               }
           }
        }
        if(!inserted) result.push_back(newInterval);
        return result;
    }

    bool isOverlap(const Interval& a, const Interval& b) {
       return !((a.end < b.start) || (a.start > b.end));
    }
};
