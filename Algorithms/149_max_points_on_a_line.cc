/*
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
*/

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

/// Iterate all points. For each point i, check all points (including i itself). There are three cases:
/// 1. duplicate point as i, track count as n_dup. n_dup is at least one
/// 2. lying along same vertical line as point i, track count as n_ver
/// 3. lying on a line of a finite slope. maintain a map of slope and count. Track the maximum of counts of all slopes as n_slp.
/// After scanning all other points, we have n_dup, n_ver, and n_slp. Then the maximum number of points lying across i is: max(n_ver, n_slp) + n_dup.
/// repeat for all points and update
/// Caveat: when calculating the slope from integer coordinates, convert the numerator to double!

class Solution {
public:
    int maxPoints(vector<Point>& points) {
        if(points.empty()) return 0;
        int maxp = 0; //at least one
        map<double, int> slopes;
        int n = points.size();
        for(int i = 0; i < n; ++i) {
            slopes.clear();
            int n_dup(0), n_ver(0);
            int n_slp(0);
            for(int j = 0; j < n; ++j) {
                if(points[i].x == points[j].x) {
                    if(points[i].y == points[j].y) n_dup++;
                    else n_ver++;
                } else {
                    double sl = double(points[j].y - points[i].y) / (points[j].x - points[i].x);
                    n_slp = max(n_slp, ++slopes[sl]);
                }
            }
            maxp = max(maxp, max(n_slp, n_ver) + n_dup);
        }
        return maxp;
    }
};
