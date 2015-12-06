/*
A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings collectively (Figure B).
Buildings Skyline Contour

The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height. Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:

    The number of buildings in any input list is guaranteed to be in the range [0, 10000].
    The input list is already sorted in ascending order by the left x position Li.
    The output list must be sorted by the x position.
    There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
*/

// divide and conquer, similar to merge sort.
// The crux is in the merge routine. For a new point, we compare it with the last height of the other array. The merge is designed so no duplicates of x coords will appear. But duplicates for the heights will appear, so need to remove them in the end.

class Solution {
public:
    typedef pair<int, int> Point;

    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<Point> skyline;
        int n = buildings.size();
        getSkyline(buildings, 0, n-1, skyline);
        return skyline;
    }
    void getSkyline(const vector<vector<int>>& buildings, int lo, int hi, vector<Point>& skyline) {
        if(lo > hi) return;
        if(lo == hi) {
            skyline.push_back(make_pair(buildings[lo][0], buildings[lo][2])); //left, height
            skyline.push_back(make_pair(buildings[lo][1], 0)); //right, 0
            return;
        }
        //now divide and conquer
        int mid = lo + (hi-lo)/2;
        vector<Point> left, right;
        getSkyline(buildings, lo, mid, left);
        getSkyline(buildings, mid+1, hi, right);
        merge(left, right, skyline);
    }
    void merge(vector<Point>& v1, vector<Point>& v2, vector<Point>& v) {
        int i = 0, j = 0, m = v1.size(), n = v2.size();
        int last_y1 = 0, last_y2 = 0;
        while(i < m || j < n) {
            int x1 = (i < m) ? v1[i].first : INT_MAX;
            int y1 = (i < m) ? v1[i].second : 0;
            int x2 = (j < n) ? v2[j].first : INT_MAX;
            int y2 = (j < n) ? v2[j].second : 0;
            if(x1 == x2) {
                v.push_back(make_pair(x1, max(y1, y2)));
                last_y1 = y1; last_y2 = y2;
                i++; j++;
            } else if(x1 < x2) {
                v.push_back(make_pair(x1, max(y1, last_y2)));
                last_y1 = y1;
                i++;
            } else {
                v.push_back(make_pair(x2, max(y2, last_y1)));
                last_y2 = y2;
                j++;
            }
        }
        //remove duplicates
        int l = 0;
        for(int k = 0; k < v.size(); ++k) {
            if(k == 0 || v[k].second != v[k-1].second) {
                v[l++] = v[k];
            }
        }
        v.resize(l);
    }
};


// An old solution

// divide and conquer, similar to merge sort.
// two caveats:
// 1. avoid duplicated heights ([1,4], [2, 4] is not allowed)
// 2. avoid duplicated coordinates, e.g. two buildings both span [1, 3] but with different heights, need to check if the current strip has same coordinate as previous
class Solution {
public:
    typedef pair<int, int> Strip;

    vector<pair<int, int> > getSkyline(vector<vector<int> >& buildings) {
        return getSkylineUtil(buildings, 0, buildings.size()-1);
    }

    //get strips for buildings[lo .. hi]
    vector<Strip> getSkylineUtil(const vector<vector<int> >& buildings, int lo, int hi) {
        vector<Strip> ret;
        if (lo > hi) return ret;
        if (lo == hi) {  //only one building
            ret.resize(2);
            ret[0] = make_pair(buildings[lo][0], buildings[lo][2]);
            ret[1] = make_pair(buildings[lo][1], 0);
            return ret;
        }
        int mid = (lo + hi) / 2;
        const vector<Strip>& left  = getSkylineUtil(buildings, lo,   mid);
        const vector<Strip>& right = getSkylineUtil(buildings, mid+1, hi);
        return merge(left, right);
    }
    
    //merge two strips
    vector<Strip> merge(const vector<Strip>& a, const vector<Strip>& b) {
        vector<Strip> ret;
        size_t m = a.size(), n = b.size();
        int side(0);
        int ha(0), hb(0), h(-1), x(INT_MIN), newh(0), newx(0);
        for(size_t i = 0, j = 0; i < m || j < n; ) {
            if(i == m) side = 1; //right
            else if(j == n) side = 0; //left
            else side = (a[i].first < b[j].first) ? 0 : 1;

            if (side == 0) { //picked a strip from a
                newx = a[i].first; 
                ha = a[i].second;  //update ha
                i++;
            } else {
                newx = b[j].first; 
                hb = b[j].second; //update hb
                j++;
            }
            newh = max(ha, hb);
            if (h != newh) { // avoid duplicated height
                if(newx == x) ret.back() = make_pair(newx, newh); //update last entry, avoid duplicated x
                else ret.push_back(make_pair(newx, newh)); //append new entry
                h = newh; //update h
                x = newx; //update x
            }
        }
        return ret;
    }
};
