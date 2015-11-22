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

/// O(n2) solution with hash table.
/// Iterate all points. For each point i, check all points after it (excluding itself). There are three cases:
/// 1. duplicate point as i, track count as n_dup.
/// 2. lying along same vertical line as point i, track count as n_ver
/// 3. lying on a line of a finite slope. maintain a map of slope and count. Track the maximum of counts of all slopes as max_line.
/// After scanning all other points, we have num_dup, num_ver, and max_line. Then the maximum number of points lying across i is: 1 + num_dup + max(max_line, num_ver), where 1 counts point i itself.
/// repeat for all points and update
/// Caveat: when calculating the slope from integer coordinates, convert the numerator to double!

class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int n = points.size();
        if(n <= 2) return n;
        int result = 0;
        unordered_map<double, int> dict;
        for(int i = 0; i < n-1; ++i) { //no need to scan last point
            int num_dup = 0, num_ver = 0, max_line = 0; //# duplicates, # points on same vertical line, max # points on any line
            dict.clear();
            //check all the points from i+1 to n
            for(int j = i+1; j < n; ++j) {
                if(points[j].x == points[i].x) {
                    if(points[j].y == points[i].y) num_dup++; //same point
                    else num_ver++; //on same vertical line
                } else { //calculate slope
                    double slope = double(points[j].y - points[i].y) / (points[j].x - points[i].x);
                    max_line = max(max_line, ++dict[slope]);
                }
            }
            result = max(result, 1 + num_dup + max(max_line, num_ver));
        }
        return result;
    }
};


/// O(n3) solution
/// Check each pair (pi, pj) and count all points lying on the line determined by pi, pj (using colinear function).
// If encountered duplicates, count them as well

class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int n = points.size();
        if(n <= 2) return n;
        int result = 0;
        for(int i = 0; i < n-1; ++i) {
            int num_dup = 1, num_col = 0;
            for(int j = i+1; j < n; ++j) {
                if(points[i].x == points[j].x && points[i].y == points[j].y) {
                    num_dup++;
                    continue;
                }
                num_col = 1; //count point[j]
                for(int k = j+1; k < n; ++k) {
                    if(colinear(points[i], points[j], points[k])) num_col ++;
                }
                result = max(result, num_dup + num_col);
            }
            result = max(result, num_dup); //deal with case where only exist duplicates, no colinear execution
        }
        return result;
    }
    
    bool colinear(Point& p, Point& q, Point& r){
        return (q.y - p.y)*(r.x - q.x) - (r.y - q.y)*(q.x - p.x) == 0;
    }
};

