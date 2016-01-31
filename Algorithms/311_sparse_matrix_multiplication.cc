/*
Given two sparse matrices A and B, return the result of AB.

You may assume that A's column number is equal to B's row number.

Example:

A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]

B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]


     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |
*/

// Solution using two vectors storing non-zero entries, for A, column-wise, for B, row-wise

class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        int m = A.size(), n = A[0].size(), p = B[0].size();
        vector<pair<int, vector<int> > > cA, rB; //non-zero entries at column i of A, or row i of B
        for(int j = 0; j < n; ++j) {
            bool first = true;
            for(int i = 0; i < m; ++i) {
                if(A[i][j] != 0) {
                    if(first) {  cA.push_back(make_pair(j, vector<int>())); first = false; }
                    cA.back().second.push_back(i);
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            bool first = true;
            for(int j = 0; j < p; ++j) {
                if(B[i][j] != 0) {
                    if(first) { rB.push_back(make_pair(i, vector<int>())); first = false; }
                    rB.back().second.push_back(j);
                }
            }
        }

        vector<vector<int> > C(m, vector<int>(p, 0));
        int p1 = 0, p2 = 0;
        //scan for cA[j] and rB[j] and see if there is duplicated entries
        while(p1 < cA.size() && p2 < rB.size()) {
            int j1 = cA[p1].first, j2 = rB[p2].first;
            if(j1 == j2) {
                for(auto k1 : cA[p1].second) {
                    for(auto k2 : rB[p2].second) {
                        C[k1][k2] += A[k1][j1]*B[j1][k2];
                    }
                }
                p1++; p2++;
            } else if(j1 < j2) p1++;
            else p2++;
        }
        return C;
    }
};
