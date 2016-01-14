/*
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9. 
*/

// Top down dynamic programming with memoization. Use an auxiliary array to store the answers. Using an unordered_map takes much longer time!
// For each number, start with 2*2, subtract as many squares as possible (e.g. 13, subtract 3 times and get 1). Then try 3*3, 4*4 ...
// Record already solved solutions in the array for later fast retrieval.

class Solution {
public:
    int numSquares(int n) {
        if(n == 0) return 1;
        if(n <= 3) return n;
        dict.resize(n+1, -1);
        dict[1] = 1;
        dict[2] = 2;
        dict[3] = 3;
        return helper(n);
    }
    int helper(int n) {
        if(dict[n] >= 0) return dict[n];
        int count = n;
        for(int i = 2; i <= n/i; ++i) {
             count = min(count, helper(n%(i*i)) + n/(i*i));
        }
        dict[n] = count;
        return count;
    }

    vector<int> dict;
};

