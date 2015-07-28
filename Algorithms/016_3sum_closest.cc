/// O(n2) solution
/// When searching the next two in linear time (as in 2-sum cases), has to scan all elements, can't break in the middle when diff changes sign!

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        
        int n = nums.size();
        int ret = 0;
        int diff = INT_MAX, min_diff = INT_MAX;
        for (int i = 0; i < n-2; ++i) {
            //find the next two in linear time
            int j = i+1, k = n-1;
            while(j < k) {
                diff = target - (nums[i] + nums[j] + nums[k]);
                if (diff > 0) j++;
                else if (diff < 0) k--;
                else return target;
                if (abs(diff) < abs(min_diff)) min_diff = diff;
            }
        }
        return target - min_diff;
    }
};
