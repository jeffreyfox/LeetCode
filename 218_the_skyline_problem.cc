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
