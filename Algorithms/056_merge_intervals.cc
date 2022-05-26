/*
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18]. 
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

// One pass simple solution after sorting interval array

bool compare(const vector<int> &a, const vector<int> &b) {
    if (a[0] == b[0]) return a[1] < b[1];
    return a[0] < b[0];
}

bool isOverlap(const vector<int> &a, const vector<int> &b) {
    return a[0] <= b[1] && b[0] <= a[1];
}

vector<int> mergeOverlap(const vector<int> &a, const vector<int> &b) {
    return {min(a[0], b[0]), max(a[1], b[1])};    
}

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        if (intervals.empty()) return {};
        std::sort(intervals.begin(), intervals.end(), compare);
        vector<int> curr = intervals[0];
        for (int i = 1; i < intervals.size(); ++i) {
            if (isOverlap(intervals[i], curr)) {
                curr = mergeOverlap(intervals[i], curr);
            } else {
                result.push_back(curr);
                curr = intervals[i];
            }
        }
        result.push_back(curr);
        return result;
    }
};
