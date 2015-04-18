/* See the first solution for the O(n) extra space version. This version uses nums itself as the table. When we find 
a positive integer i, we should put it in the right position nums[i-1], and put original values there in correct positions
as well. This requires a while loop with swap functions. For an array of n numbers, it is guaranteed that the missing positive
lies between 1 and n+1. When it is between 1 and n, then at least one entry in nums is not filled properly, and we return that
values. When it is n+1, then all entries are filled properly, and we simply return n+1.
*/
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        //uses nums[] itself as indexing table. nums[i] should store i+1
        for(int i = 0; i < n; ++i) {
            int v = nums[i];
            while(v >= 1 && v <= n && v != nums[v-1]) { //swap
                swap(v, nums[v-1]);
            }
        }
        for(int i = 0; i < n; ++i) {
            if(nums[i] != i+1) return i+1;
        }
        return n+1;
    }
    
    void swap(int &a, int &b) {
        int t = a; a = b; b = t;
    }
};
