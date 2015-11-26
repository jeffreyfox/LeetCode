/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2. 
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

//Solution 1: sort the ending point according to its coordinate and type (start/end). If ties on coordinate, end goes before start
//Then do sweeping line and count. When see a start point, increment count, otherwise decrement count.

struct EndPoint {
    int val;
    int type; //0 for starting, 1 for ending
    EndPoint(): val(0), type(0) {}
    EndPoint(int v, int t) : val(v), type(t) {}
};

bool compare(const EndPoint& a, const EndPoint& b) {
    if(a.val == b.val) return a.type < b.type;
    else return a.val < b.val;
}


class Solution {
public:

    int minMeetingRooms(vector<Interval>& intervals) {
        int n = intervals.size();
        if(n <= 1) return n;
        vector<EndPoint> points(2*n);
        for(int i = 0; i < n; ++i) {
            points[2*i] = EndPoint(intervals[i].start, 2);
            points[2*i+1] = EndPoint(intervals[i].end, 1);
        }
        sort(points.begin(), points.end(), compare);
        int count = 0, result = 0;
        for(int i = 0; i < 2*n; ++i) {
            if(points[i].type == 2) { //is start point
               count++;
               result = max(result, count);
            } else count--;
        }
        return result;
    }
};


//A simpler solution: use a map to keep order, and count individual points, then iterate orderly through map
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> dict;
        int n = intervals.size();
        if(n <= 1) return n;
        for(int i = 0; i < n; ++i) {
            dict[intervals[i].start]++;
            dict[intervals[i].end]--;
        }
        int count = 0, max_count = 0;
        for(auto it : dict) { //ordered iterator
            count += it.second;
            max_count = max(count, max_count);
        }
        return max_count;
    }
};

