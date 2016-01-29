/*
The gray code is a binary numeral system where two successive values differ in only one bit.
Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.
For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
00 - 0
01 - 1
11 - 3
10 - 2
Note:
For a given n, a gray code sequence is not uniquely defined.
For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.
For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.
*/

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

// Solution 2 using one single loop
class Solution {
public:
   vector<int> grayCode(int n) {
        if(n < 0) return vector<int>();
        vector<int> result(1 << n, 0); //pow(2, n)
        for(int j = 1, size = 1; j < result.size(); ++j) {
            if(j == size)  size <<= 1;
            result[j] = result[size-j-1] + (size >> 1);
        }
        return result;
    }
};
