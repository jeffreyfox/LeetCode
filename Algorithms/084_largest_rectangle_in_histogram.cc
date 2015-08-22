/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given height = [2,1,5,6,2,3],
return 10. 
*/

/// using a stack to store positions. Compare the newly encountered height with that in the stack. 
/// If higher, push into stack. If lower, then we know that the previous height can only reach left of here.
/// Initially push a sentinel element to back of height array

class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        if(height.empty()) return 0;
        height.push_back(0);
        deque<int> s; //stack for positions
        int n = height.size();
        int max_area = 0;
        for(int i = 0; i < n; ++i) {
             while(!s.empty() && height[s.back()] > height[i]) {
                int h = height[s.back()];
                s.pop_back();
                int j = s.empty() ? 0 : s.back()+1;
                max_area = max(max_area, h*(i-j));
            }
            s.push_back(i);
        }
        return max_area;
    }

};
