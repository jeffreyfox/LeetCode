/*
Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm?

Hint:

Expected runtime complexity is in O(log n) and the input is sorted.
*/

// binary search, similar to 274 except that here the array is sorted in ascending order.

class Solution {
public:
    int hIndex(vector<int>& citations) {
        if(citations.empty()) return 0;
        int n = citations.size();
        int lo(0), hi(n-1);
        //[0 .. lo-1] have n-i > citations[i], [hi+1, end) have n-i <= citations[i], return n-lo
        while(lo <= hi) {
            int mid = lo + (hi-lo)/2;
            if(n-mid > citations[mid]) lo = mid+1;
            else hi = mid-1;
        }
        return n-lo;
    }
};
