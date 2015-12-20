/*
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing all 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Return 4. 
*/

// Same idea as maximal rectangle, use routine in finding largest rectangle. Except when calculating area, use min(height, length)^2. See solutions in 085 maximal rectangle

class Solution {
public:
    int maximalSquare(vector<vector<char> > &matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> height(n, 0);
        int max_area = 0;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                height[j] = (matrix[i][j] == '1') ? height[j]+1 : 0;
            }
            max_area = max(max_area, largestSquareArea(height));
        }
        return max_area;
    }

    int largestSquareArea(vector<int>& height) {
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
                int side = min(h, i-j);
                max_area = max(max_area, side*side);
            }
            s.push_back(i);
        }
        return max_area;
    }
};
