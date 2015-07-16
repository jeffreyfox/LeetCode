/* A not so smart solution using O(n) auxiliary space. Basically we use a table to store occurrences of positive integers
in nums. See solution 2 for O(1) space solution.
*/
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        vector<int> flag(n, 0); //flag[i] stores flag for i+1
        for(int i = 0; i < n; ++i) {
            if(nums[i] >= 1 && nums[i] <= n) flag[nums[i]-1] = 1;
        }
        for(int i = 0; i < n; ++i) {
            if(flag[i] == 0) return i+1;
        }
        return n+1;
    }
};
