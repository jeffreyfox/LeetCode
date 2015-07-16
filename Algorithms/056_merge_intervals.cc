/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
 
bool compare(const Interval &a, const Interval &b) {
    if(a.start < b.start) return true;
    if(a.start > b.start) return false;
    return a.end < b.end;
}

class Solution {
public:

    vector<Interval> merge(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), compare);
        vector<Interval> s; //stack 
        int n = intervals.size();
        for(int i = 0; i < n; ++i) {
            Interval it = intervals[i];
            while(!s.empty() && isOverlap(s.back(), it)) { //overlap
                it = mergeTwo(s.back(), it);
                s.erase(s.end()-1); //stack pop
            } 
            //now either stack is empty, or there is no overlap
            s.insert(s.end(), it); //stack push
        }
        return s; //return whole stack
    }
    
    bool isOverlap(const Interval& a, const Interval &b) {
        return (a.start <= b.end && b.start <= a.end);
    }
    
    Interval mergeTwo(const Interval &a, const Interval &b) {
        Interval it;
        it.start = min(a.start, b.start);
        it.end = max(a.end, b.end);
        return it;
    }
};
