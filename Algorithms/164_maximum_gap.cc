/*
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Try to solve it in linear time/space.

Return 0 if the array contains less than 2 elements.

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
*/

// 2021.
// Solution using radix sort.
// Caveats:
// Integer overflow. Needs to use long long.
class Solution {
public:
    int maximumGap(vector<int>& nums) { 
        vector<int> sorted = nums;
        
        // radix sort
        for (long long base = 1; base <= kMax; base *= 10) {
            sorted = countingSort(sorted, base);
        }
        
        // Linear scan
        int result = 0;
        for (int i = 1; i < sorted.size(); ++i) {
            result = max(result, sorted[i] - sorted[i-1]);
        }
        return result;
    }
    
    vector<int> countingSort(vector<int>& nums, long long base) {
        vector<int> counts(10);        
        // Construct counts
        for (const int num : nums) {
            int digit = (num / base) % 10;
            counts[digit] ++;
        }
        // Accumulate
        for (int i = 1; i < counts.size(); ++i) {
            counts[i] += counts[i-1];
        }
        // Put integers into the correct location
        vector<int> result(nums.size());
        for (int k = nums.size()-1; k >= 0; --k) {
            int digit = (nums[k] / base) % 10;
            int idx = --counts[digit];
            result[idx] = nums[k];
        }
        return result; 
    }
    
private:
    const long long kMax = 1000'000'000LL;
};

// 2015.
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
        int min_val = nums[0], max_val = nums[0];
        for(int i = 1; i < n; i++) {
            min_val = min(min_val, nums[i]);
            max_val = max(max_val, nums[i]);
        }
        if(min_val == max_val || min_val == max_val-1) return max_val - min_val;
        
        int nbuck = n+1;
        vector<pair<int, int> > buckets(nbuck, make_pair(-1, -1));//pair is for lower and higher bounds
        double blen = (max_val-min_val)/(double)nbuck; //length of the bucket interval
        //put numbers in buckets, which stores the lower and higher bounds of each interval
        for(int i = 0; i < n; i++) {
            int ib = (nums[i] - min_val) / blen;
            if(ib == nbuck) ib = nbuck-1;
            if(buckets[ib].first == -1) buckets[ib].first = buckets[ib].second = nums[i];
            else {
                buckets[ib].first = min(buckets[ib].first, nums[i]);
                buckets[ib].second = max(buckets[ib].second, nums[i]);
            }
        }
        //scan interval and find maximum gap
        int max_gap = 0;
        //buckets[0] and buckets[ib-1] surely is defined (min, max)
        int right = buckets[0].second;
        for(int i = 1; i < nbuck; i++) {
            if(buckets[i].first == -1) continue;
            max_gap = max(max_gap, buckets[i].first - right);
            right = buckets[i].second;
        }
        return max_gap;
    }
};

