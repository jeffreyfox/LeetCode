// Parabola.
// If a > 0, the largest has to be on either end. Move from either end and fill the result from largest to smallest.
// If a <= 0 the smallest has to be on either end. Move from either end and fill the result from smallest to largest.
class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        int n = nums.size();        
        for (int i = 0; i < n; ++i) {
            nums[i] = a*nums[i]*nums[i] + b*nums[i] + c;
        }
        vector<int> result(n, 0);
        int lo = 0, hi = n-1;
        if (a > 0) {
            int j = n-1;
            while (lo <= hi) {
                if (nums[lo] < nums[hi]) result[j--] = nums[hi--];
                else result[j--] = nums[lo++];
            }
        } else {
            int j = 0;
            while (lo <= hi) {
                if (nums[lo] > nums[hi]) result[j++] = nums[hi--];
                else result[j++] = nums[lo++];
            }
        }
        return result;
    }
};
