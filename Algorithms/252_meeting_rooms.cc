/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return false. 
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

// First sort the interval according to starting times, then check whether each ajacent pair overlaps
// Criteria for not overlap:
// a.start <= b.end OR b.start <= a.end
// Then criteria for overlap is (applying boolean logic)
// a.start > b.end AND b.tart > a.end

bool compare_start(const Interval& a, const Interval& b) {
    return a.start < b.start;    
}

class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        if(intervals.empty()) return true;
        int n = intervals.size();
        if(n == 1) return true;
        sort(intervals.begin(), intervals.end(), compare_start);
        for(int i = 1; i < n; ++i) {
            if(intervals[i].start < intervals[i-1].end && intervals[i-1].start < intervals[i].end) return false;
        }
        return true;
    }
};
