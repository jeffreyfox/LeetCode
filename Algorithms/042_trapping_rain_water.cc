/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6. 
*/

/// Two pointers on each end (l, r).
/// Maintain the current minimum water level as level
/// Scan from two sides until l and r meet, collect water amounts at each position
/// Given l and r, the minimum water level should be level = min(height[l], height[r])
/// Always scan from the lower side (between l and r) because it determines the current water level
/// When the encountered height is below level, then collect the difference and add to water amount
/// When the encountered height is above level, no water can be stored at this point. But the water level can rise (determined by minimum of this height and height of other end), so simply update level.
/// Use nested while loops

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0;
        int l(0), r(n-1);
        int level(0), water(0);
        while(l < r) {
            level = min(height[l], height[r]);
            if(height[l] < height[r]) { //left side lower
                while(++l < r && height[l] <= level) water += (level-height[l]);
            } else {
                while(--r > l && height[r] <= level) water += (level-height[r]);
            }
        }
        return water;
    }
};
