/*
We are given a list schedule of employees, which represents the working time for each employee.

Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.

Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.

(Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays. For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined).  Also, we wouldn't include intervals like [5, 5] in our answer, as they have zero length.

 

Example 1:

Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation: There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.
Example 2:

Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]
 

Constraints:

1 <= schedule.length , schedule[i].length <= 50
0 <= schedule[i].start < schedule[i].end <= 10^8
*/

/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

/// Flatten the intervals into 1D vector and sort them according to start time. Then perform linear scan to find gaps.
bool compare(const Interval &a, const Interval &b) {
    if (a.start == b.start) return a.end < b.end;
    return a.start < b.start;
}

bool isOverlap(const Interval &a, const Interval &b) {
    return a.start <= b.end && b.start <= a.end;
}

Interval merge(const Interval &a, const Interval &b) {
    return Interval(min(a.start, b.start), max(a.end, b.end));
}

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        vector<Interval> all_schedules;
        for (const auto &entry : schedule) {
            all_schedules.insert(all_schedules.end(), entry.begin(), entry.end());
        }
        std::sort(all_schedules.begin(), all_schedules.end(), compare);
        
        vector<Interval> result;
        if (all_schedules.empty()) return {};
        Interval curr = all_schedules[0];
        for (int i = 1; i < all_schedules.size(); ++i) {
            if (isOverlap(all_schedules[i], curr)) {
                curr = merge(all_schedules[i], curr);
            } else {
                // The two intervals don't overlap. Insert the "gap" to result
                result.push_back(Interval(curr.end, all_schedules[i].start));
                curr = all_schedules[i];
            }            
        }
        return result;
    }
};
