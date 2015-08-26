/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
*/

// Maintain a range of indices reachable by at most njumps. Proceed to next one, when reaching the end break.
//             [  2   3   1   1   4 ]
//njump = 0      i,j
//njump = 1           i   j
//njump = 2                   i   j

class Solution {
public:
   int jump(vector<int>& nums) {
       if(nums.empty()) return 0;
       int n = nums.size();
       if (n == 1) return 0;
       int i(0), j(0), k(0);
       int njump = 0;
       // nums[i .. j] are reachable by njump jumps
       while(i <= j && j < n-1) {
          int max_r = -1; //maximum reachable
          for(k = i; k <= j; ++k) {
              max_r = max(max_r, k+nums[k]);
          }
          i = j+1; j = max_r;
          njump ++;
       }
       return (i <= j) ? njump : -1;
   }
};
