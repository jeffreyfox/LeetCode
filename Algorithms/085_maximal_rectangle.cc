/*
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area. 
*/

// Use the routine of finding the largest rectangle in the histogram.
// Scan from top to bottom, find largest rectangle at current level. 

class Solution {
public:
    int maximalRectangle(vector<vector<char> >& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> height(n, 0);
        int max_area = 0;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                height[j] = (matrix[i][j] == '1') ? height[j]+1 : 0;
            }
            max_area = max(max_area, largestRectangleArea(height));
        }
        return max_area;
    }

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
