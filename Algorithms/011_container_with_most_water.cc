/*
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container. 
*/

/*
Similar idea to "trapping rain water". Maintain two pointers and find the minimum water level deterimed by the two pointers. Move from the side with lower height, stop when two pointers meet.
The height of container is the smaller of the two ends. Proceed by moving the lower point inwards, because we can proove that the interval between lo and hi is the widest one possible for the container of height of height[lo].
Proceeding from higher point is wrong! e.g.
height:   3 9 1 1
position: 0 1 2 3

l = 0, h = 3 => area = 3
if we move from higher point, we missed [0, 1] with area 6.
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int area = 0;
        int n = height.size();
        if(n <= 1) return 0;
        int l(0), r(n-1);
        while(l < r) {
            area = max(area, min(height[l], height[r])*(r-l));
            if(height[l] < height[r]) l++;
            else r--;
        }
        return area;
    }
};
