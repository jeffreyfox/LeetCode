/*
There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.
*/

// Solution: Dynamic programming
// Keep the cost for painting the first k houses with last house colored as R/G/B.
// The k+1 house can choose among R/G/B, with cost as
// cost_so_far[R]:  cost[k+1][R] + min(cost_so_far[G], cost_so_far[B])
// and similar for other two cases.

class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if(costs.empty() || costs[0].empty()) return 0;
        int n = costs.size();
        vector<int> cost_so_far(3, 0);
        for(int i = 0; i < n; ++i) {
            int t0 = min(cost_so_far[1], cost_so_far[2]) + costs[i][0];
            int t1 = min(cost_so_far[0], cost_so_far[2]) + costs[i][1];
            int t2 = min(cost_so_far[0], cost_so_far[1]) + costs[i][2];
            cost_so_far[0] = t0;
            cost_so_far[1] = t1;
            cost_so_far[2] = t2;
        }
        return min(min(cost_so_far[0], cost_so_far[1]), cost_so_far[2]);
    }
};
