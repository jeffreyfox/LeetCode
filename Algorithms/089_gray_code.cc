// Dynamic programming, start from 1, expand to n:
// 1: (0 1)
// 2: (0 1, 2+1 2+0) = (0 1 3 2)
// 3: (0 1 3 2, 4+2 4+3 4+1 4+0) = (0 1 3 2 6 7 5 4)
// One array is enough (no need to use another array to store temporary results
// Be careful of corner case n = 0 (somehow should return [0])

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res;
        if (n == 0) return vector<int>(1, 0);
        res.resize(2, 0);
        res[1] = 1;
        for (int i = 1; i < n; ++i) {
            int size = res.size();
            res.resize(size*2);
            for(int j = 0; j < size; ++j) {
               res[j+size] = (1 << i) + res[size-1-j];
            }
        }
        return res;
    }
};
