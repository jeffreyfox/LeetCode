// same idea as 54. spiral matrix 

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int> > matrix;
        if (n <= 0) return matrix;
        matrix.resize(n, vector<int>(n, 0));
        int i(0), j(0);
        int l(0), r(n-1), t(0), b(n-1);
        int state = 0; //0: left, 1: down, 2: right, 3: up
        int tot = n*n;
        for (int k = 1; k <= tot; ++k) {
            matrix[i][j] = k;
            move(i, j, l, r, t, b, state);
        }
        return matrix;
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
