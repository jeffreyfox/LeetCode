// Use a move function to traverse the matrix.
// Keep track of the current boundaries of the matrix, and the current state indicating moving direction
// When moving direction changes, update boundary accordingly
// Return when exactly m*n elements have been visited

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) return vector<int>();
        int n = matrix[0].size();
        if (n == 0) return vector<int>();
        int mn = m*n;
        int i(0), j(0);
        int l(0), r(n-1), t(0), b(m-1);
        int state = 0; //0: left, 1: down, 2: right, 3: up
        vector<int> ret(mn, 0);
        for (int k = 0; k < mn; ++k) {
            ret[k] = matrix[i][j];
            move(i, j, l, r, t, b, state);
        }
        return ret;
    }
    
    void move(int& i, int& j, int& l, int& r, int& t, int& b, int& state) {
        switch (state) {
        case 0: //moving right
            if (j < r) j++;
            else { t++; i++; state = 1; } //change to down
            break;
        case 1: //moving down
            if (i < b) i++;
            else { r--; j--; state = 2; } //change to left
            break;
        case 2: //moving left
            if (j > l) j--;
            else { b--; i--; state = 3; } //change to up
            break;
        case 3: //moving up
            if (i > t) i--;
            else { l++; j++; state = 0; } //change to left
            break;
        default:
            break;
        }
    }
};
