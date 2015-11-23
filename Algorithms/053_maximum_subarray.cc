/*
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

click to show more practice.
More practice:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/

// Solution 1. Divide and conquer.
// Find max from left sub array, right sub array, and crossing arrays.
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        return maxSubArrayAux(nums, 0, nums.size()-1);
    }
    
    int maxSubArrayAux(vector<int>& nums, int lo, int hi) {
        if(lo > hi) return INT_MIN;
        if(lo == hi) return nums[lo]; //only one element
        int mid = lo + (hi - lo) / 2; //break array at mid | mid+1
        int max1 = maxSubArrayAux(nums, lo, mid);
        int max2 = maxSubArrayAux(nums, mid+1, hi);
        int max3 = maxCrossing(nums, lo, hi, mid);
        return max(max(max1, max2), max3);
    }
    
    int maxCrossing(vector<int>& nums, int lo, int hi, int mid) {
        int left_sum = nums[mid], max_left_sum = left_sum;
        int right_sum = nums[mid+1], max_right_sum = right_sum;
        int jleft = mid-1, jright = mid+2;
        while(jleft >= lo) {
            left_sum += nums[jleft];
            max_left_sum = max(max_left_sum, left_sum);
            jleft--;
        }
        while(jright <= hi) {
            right_sum += nums[jright];
            max_right_sum = max(max_right_sum, right_sum);
            jright++;
        }
        return max_left_sum + max_right_sum;
    }
};


/// Solution 2 dynamic programming.
/*
Maximum ending at nums[k] can be obtained from nums[k] and maximum ending at nums[k-1].
1. if max ending at nums[k-1] is positive, then we simply add nums[k] to obtain max ending at nums[k].
2. if max ending at nums[k-1] is negative, then we can discard everything before nums[k], and use nums[k] as max ending at nums[k].
When assigning max_all, using conditional clause (as below) is 4ms faster than using std::max.
*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        int max_ending_here = 0, max_all = INT_MIN;
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            max_ending_here = max_ending_here > 0 ? (max_ending_here + nums[i]) : nums[i];
            if(max_all < max_ending_here) max_all = max_ending_here;
        }
        return max_all;
    }
};
