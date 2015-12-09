/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6. 
*/

/*
We notice that the amount of water trapped at position[i] is bounded by the *lower* of the peak position at its left and peak position at its right. This has suggested a two-way search, instead of single-direction scan. We use two pointers, l and r, initially at the two boundaries of array. Then, the water level is limited by the lower of hl = height[l] and hr = height[r]. We move from the lower side towards the other side., here we assume it is the left side. We also keep track of the current water level at each position. Two cases:
1) if we see a higher point than hl. this will raise the water level to the new height. No water can be trapped here.
2) if we see a lower point than hl, then water will be trapped here and the amount is the difference between current water level and current height at this position.

Every time we move one step, we compare height[l] and height[r], and we always move from the lower side until the two meets.

Caveats:
store height[l] and height[r] as temporary hl and hr, so that when l or r moves, we are comparing to the old value of hl and hr. We need to properly update hl and hr before proceeding to next step.

One while loop.
*/

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int i(0), j(n-1);
        int sum(0);

        int l = i, r = j;
        while (i < j-1) {
            int level = min(height[l], height[r]);
            if (height[l] < height[r]) { //left side lower
                i++;
                if (height[i] < level) sum += level - height[i];
                else l = i;
            } else { //right side lower
                j--;
                if (height[j] < level) sum += level - height[j];
                else r = j;
            }
        }
        return sum;
    }
};


/// Another solution using nested while loops.
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
