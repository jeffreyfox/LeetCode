/*
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area. 
*/

// Solution 1. Use the routine of finding the largest rectangle in the histogram.
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

/*
Solution 2 using dynamic programming. For each row, use three arrays, left/right/height to store the left and right boundary and height of maximum rectangle enclosing matrix[i][j] for the rows seen so far (just like the bars in the histogram problem). Use the values at step i to calculate the values at step i+1.

             +
         +   +
         +   + +
         + + + +
index: 0 1 2 3 4
left: -1 1 1 3 3
right: 5 1 4 3 4
height:0 3 1 4 2

Now check the new row, we track the first left seen so far.

           +
       +   +
       +   + +
       + + + +
     0 1 2 3 4 
     + + +  : cur_left = 0
the new left is simply the maximum of old left and cur_left
the new right is simply the minimum of old right and cur_right
We assign cur_left values in an eager way: whenever we see a '0', we asisgn cur_left to j+1.

Caveat: 
1. for '0' entries, left[i] can be -1, but right[i] should be n, due to the min operation used to update its value.
2. Remember to properly initialize cur_left and cur_right when scanning each row.
*/

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> left(n, -1), right(n, n), height(n, 0);
        int cur_left = 0, cur_right = 0;
        int max_area = 0;
        for(int i = 0; i < m; ++i) {
            cur_left = 0; cur_right = n-1; //initialize
            for(int j = 0; j < n; ++j) { //scan left to right
                height[j] = (matrix[i][j] == '0') ? 0 : height[j]+1;
                if(matrix[i][j] == '0') {
                    left[j] = -1;
                    cur_left = j+1; //pre-assign cur_left to next 
                } else {
                    left[j] = max(left[j], cur_left);
                }
            }
            for(int j = n-1; j >= 0; --j) { //scan right to left
                if(matrix[i][j] == '0') {
                    right[j] = n; //cannot be -1 due to the min operation!
                    cur_right = j-1; //pre-assign cur_right to next
                } else {
                    right[j] = min(right[j], cur_right);
                }
            }
            //now we have left[j], right[j], and height[j] in place
            for(int j = 0; j < n; ++j) {
                max_area = max(max_area, height[j]*(right[j] - left[j] + 1));
            }
        }
        return max_area;
    }
};
