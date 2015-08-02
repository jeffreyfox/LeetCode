// O(n) greedy solution: start from right, scan left and find all elements reachable to end
// e.g. [4sa 3 4 1 0 2]
// search starts from 0, and found 4 reachable to end. Then problem reduces to the [4 3 4] subarray.

class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.empty()) return false;
        int n = nums.size();
        if(n == 1) return true;
        //start from right to left, find all elements reachable to end
        int end = n-1, i(0);
        while (end > 0) {
            i = end - 1;
            while (i >= 0 && i + nums[i] < end) i--;
            if (i < 0) return false; //not found
            end = i;
        }
        return true;
    }
};
