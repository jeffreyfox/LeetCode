/*
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Try to solve it in linear time/space.

Return 0 if the array contains less than 2 elements.

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
*/

// Solution using bucket sort.
/*
1. first find the maximum and minimum of the array
2. partition the numbers into n-1 buckets, based on the position in the [min, max] interval. Also put min, max to the buckets
3. According to pigeon-hole, at least one bucket will be empty. And the maximum difference will be straddling across these empty regions (because the legnth is larger than bucket interval, and the difference within a bucket is smaller than bucket interval).
4. Scan all buckets, calculate the difference straddling across all empty buckets, and return the maximum among all of them.

The trick to put max and min to buckets is to avoid array index bound checks (i < 0, i > nb-1). This ensures that the first and last bucket is always filled.

Caveats:
a. max should be the last bucket, should avoid the integer out-of-bounds error.
b. number of buckets should be 1 less of total number of points, so if min/max are included, it should be n-1 !
c. there can be multiple empty buckets, and they can be continuous! So need to keep track of left-most boundary of the continuous empty bucket set.
d. integer/double conversion when doing integer division to find bucket lengths!
e. span / n-1 is wrong, should be span /(n-1)
*/

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return 0;
        if(n == 2) return abs(nums[0] - nums[1]);
        int minimum = INT_MAX, maximum = INT_MIN;
        for(int i = 0; i < n; ++i) {
            if(nums[i] > maximum) maximum = nums[i];
            if(nums[i] < minimum) minimum = nums[i];
        }
        int span = maximum - minimum;
        if(span == 0) return 0;
        //put the left n numbers into n+1 buckets, tracking the minimum and maximum in each bucket
        int nb = n+1; 
        double bucket_len = double(span) / nb;
        vector<pair<int, int> > buckets(nb, make_pair(-1, -1));
        for(int i = 0; i < n; ++i) {
            int ib = (nums[i] - minimum) / bucket_len;
            //put maximum in last bucket
            if(ib == nb) ib = nb-1;
            if(buckets[ib].first == -1) buckets[ib].first = buckets[ib].second = nums[i];
            else {
                if(nums[i] < buckets[ib].first) buckets[ib].first = nums[i];
                if(nums[i] > buckets[ib].second) buckets[ib].second = nums[i];
            }
        }
        //now scan all buckets and find all empty ones
        int max_diff = INT_MIN, diff = 0;
        int left = -1, right = -1; //left and right boundary of empty space
        for(int ib = 0; ib < nb; ++ib) {
            if(buckets[ib].first == -1) { //can't be first or last bucket
                if(left == -1) left = buckets[ib-1].second;
                right = buckets[ib+1].first;
            } else { //calculate previous
                max_diff = max(max_diff, right - left);
                left = right = -1;
            }
        }
        return max_diff;
    }
};
