/*
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Ensure that numbers within the set are sorted in ascending order.

Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]


Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]
*/

/// Use DFS. Choose number in ascending order, track how many numbers have chosen, and the next available number to choose.
// e.g. k = 3, n = 9, for [2,3] then chosen 2 numbers, and the next one can be chosen from 4 to 9.

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int> > ret;
        vector<int> tmp;
        dfs(k, n, 0, 1, tmp, ret);
        return ret;
    }
    //i-th number, residue is res, max to be used is j
    void dfs(int k, int res, int i, int j, vector<int>& tmp, vector<vector<int> >& ret) {
        if (res == 0) {
            if(i == k) ret.push_back(tmp); //found
            return;
        }
        tmp.push_back(0);
        for (int q = j; q <= 9 && q <= res; ++q) {
            tmp.back() = q;
            dfs(k, res-q, i+1, q+1, tmp, ret);
        }
        tmp.pop_back();
    }
};
