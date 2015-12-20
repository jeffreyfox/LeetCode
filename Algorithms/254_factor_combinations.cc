/*
Numbers can be regarded as product of its factors. For example,

8 = 2 x 2 x 2;
  = 2 x 4.

Write a function that takes an integer n and return all possible combinations of its factors.

Note:

    Each combination's factors must be sorted ascending, for example: The factors of 2 and 6 is [2, 6], not [6, 2].
    You may assume that n is always positive.
    Factors should be greater than 1 and less than n.

Examples:
input: 1
output:

[]

input: 37
output:

[]

input: 12
output:

[
  [2, 6],
  [2, 2, 3],
  [3, 4]
]

input: 32
output:

[
  [2, 16],
  [2, 2, 8],
  [2, 2, 2, 4],
  [2, 2, 2, 2, 2],
  [2, 4, 4],
  [4, 8]
]
*/

// Recursive DFS solution. Avoid adding [n] to solution (checking tmp.empty()).
// Also avoid pushing duplicated entries, e.g. [2, 2, 3], [2, 3, 2]. This is done by the j*j <= n condition in the loop.
class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int> > result;
        if(n <= 2) return result; //empty
        vector<int> tmp;
        dfs(n, 2, tmp, result); // start searching factors from 2 to sqrt(n)
        return result;
    }
    void dfs(int n, int i, vector<int>& tmp, vector<vector<int> >& result) {
        tmp.push_back(0);
        if(!tmp.empty()) { //push n itself
            tmp.back() = n;
            result.push_back(tmp);
        }
        //now check factors
        for(int j = i; j*j <= n; ++j) {
            if(n % j != 0) continue; //not a factor
            tmp.back() = j;
            dfs(n/j, j, tmp, result); //now start searching from j
        }
        tmp.pop_back();
    }
};

