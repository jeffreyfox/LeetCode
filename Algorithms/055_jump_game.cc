/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false. 
*/

/* Solution 1. Maintain a variable (step) for the maximum steps at each position. Scan forward, say the maximum step at position i is step, then we move one step further, the maximum step can be either step-1 (because we moved one step forward), or the maximum step at i+1. Thus
step = max(step-1, nums[i]);
If step = 0, then cannot jump.
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        if(nums[0] == 0) return false;
        int step = nums[0];
        for(int i = 1; i < n-1; ++i) {
            step = max(step-1, nums[i]);
            if(step <= 0) return false;
        }
        return true;
    }
};

/*
Solution 2. Similar to Solution 1, but Keep a variable (rightEnd) for the maximum reachable index at each position. Scan forward, if the current position is beyond the rightEnd, then cannot jump. If rightEnd exceeds n-1, then can jump.
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        int rightEnd = 0, i = 0;
        for(int i = 0; i <= rightEnd; i++) {
            rightEnd = max(rightEnd, i + nums[i]);
            if(rightEnd >= n-1) return true;
        }
        return false;
    }
};

/*
Solution 3. Dynamic programming, each step, maintain a range [lo, hi] reachable from beginning, then scan all elements in the range, and calculate the newly reachable range as [hi+1, max( nums[i]+i) for all i between lo and hi]. If hi is not increased in the newly range, then cannot jump.
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        int lo = 0, hi = 0;
        while(hi < n-1) {
           int tmp = hi;
           for(int i = lo; i <= tmp; ++i) {
               hi = max(hi, i+nums[i]);
           }
           if(hi == tmp) return false;
           lo = tmp+1;
        }
        return true;
    }
};

/*
Solution 4. Start from right and scan to left. Find first element reachable to end, and make that element the new end.
e.g. [4 3 4 1 0 2]
search starts from 0, and found 4 reachable to end. Then problem reduces to the [4 3 4] subarray.
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        int i = n-1, j = 0;
        while(i > 0) {
           j = i-1;
           while(j >= 0 && nums[j] < i-j) { //find first element that can reach to nums[i]
              j--;
           }
           if(j == -1) return false; //not found
           i = j;
        }
        return true;
    }
};
