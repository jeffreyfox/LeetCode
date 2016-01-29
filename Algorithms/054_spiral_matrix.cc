/*
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
*/

// Keep track of the current boundaries of the matrix, and the current state indicating moving direction
// When moving direction changes, update boundary accordingly
// Return when exactly m*n elements have been visited

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        if(matrix.empty() || matrix[0].empty()) return result;
        int m = matrix.size(), n = matrix[0].size(), mn = m*n;
        top = 0; bottom = m-1; left = 0; right = n-1;
        state = 0;
        result.resize(mn);
        int i(0), j(0), k(0);
        while(k < mn) {
            result[k++] = matrix[i][j];
            //update boundary and go to next step
            switch(state) {
                case 0:
                    if(j < right) j++; // move right
                    else { state = 1; i++; top++; } //start to move down
                    break;
                case 1:
                    if(i < bottom) i++; // move down
                    else { state = 2; j--; right--; } //start to move left
                    break;
                case 2:
                    if(j > left) j--; //move left
                    else { state = 3; i--; bottom--; } //start to move up
                    break;
                case 3:
                    if(i > top) i--; //move up
                    else { state = 0; j++; left++; } //start to move right 
                    break;
                default:
                    break;
            }
        }
        return result;
    }
    int top, bottom, left, right, state;
};
