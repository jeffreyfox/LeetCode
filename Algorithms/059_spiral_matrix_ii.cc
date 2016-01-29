/*
Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/

// same idea as 54. spiral matrix 

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int> > result;
        if(n == 0) return result;
        top = 0; bottom = n-1; left = 0; right = n-1;
        state = 0;
        result.resize(n, vector<int>(n, 0));
        int i(0), j(0), k(1), nn(n*n);
        while(k <= nn) {
            result[i][j] = k++;
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
