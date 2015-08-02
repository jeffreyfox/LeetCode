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
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        int n = intervals.size();
        vector<Interval> ret;
        for (int i = 0; i < n; ++i) {
            const Interval& curr = intervals[i];
            if (isOverlap(curr, newInterval))
                newInterval = getMergedInterval(curr, newInterval);
            else if (newInterval.start < curr.start) { //non-overlap, newInterval smaller
                ret.push_back(newInterval);
                newInterval = curr;
            } else ret.push_back(curr);
        }
        ret.push_back(newInterval);
        return ret;
    }
    
    bool isOverlap(const Interval& i1, const Interval& i2) {
        return (i1.start <= i2.end && i2.start <= i1.end);
    }
    
    Interval getMergedInterval(const Interval& i1, const Interval& i2) {
        return Interval(min(i1.start, i2.start), max(i1.end, i2.end));
    }
};
