// Linear scan. O(n2).
// Sort the input array.
// First loop finds the first side, nums[i]
// second and third loop finds the 2nd and 3rd sides simultaneously. 
// Need to handle the case where input contains 0.
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int result = 0;
        int n = nums.size();
        for (int i = 0; i < n-2; ++i) {
            if (nums[i] == 0) continue;
            int k = i+2;
            for (int j = i+1; j < n-1; ++j) {
                while (k < n && nums[k] < nums[i] + nums[j]) k++;
                result += k-j-1;
            }
        }
        return result;
    }
};
