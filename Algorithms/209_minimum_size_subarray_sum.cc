/// sliding window [j .. i], calculate sum on-the-fly
/// when sum >= s, move j forward as much as possible until sum < s, then i-j+2 gives the minimum length ending at i. 
/// Keep moving i forward until end

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int j = 0;
        int sum = 0;
        int minL = INT_MAX;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (sum >= s) {
                while (sum >= s) sum -= nums[j++]; //move j forward, subtract the front
                if (i-j+2 < minL) minL = i-j+2;
            }
        }
        return (minL == INT_MAX) ? 0 : minL;
    }

};
