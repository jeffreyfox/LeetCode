/*
There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

Follow up:
Could you solve it in O(nk) runtime?
*/

/* Dynamic programming. Similar to 256 paint house where k=3. To make it O(nk), we need to find the minimum among k-1 colors out of k colors. To do this in O(k) time, notice that the minimum among k-1 colors has n cases, n-1 of them end up with the minimum elements of the k colors, and the other one end up with the second minimum element. So we just keep track of the minimum and second minimum element of the k colors.
*/

class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if(costs.empty() || costs[0].empty()) return 0;
        int n = costs.size();
        int ncolor = costs[0].size();
        vector<int> cost_so_far(ncolor, 0);
        vector<int> tmp(ncolor, 0);
        int min_cost = INT_MAX, second_min_cost = INT_MAX;
        int min_cost_color = 0, second_min_cost_color = 0;
        for(int i = 0; i < n; ++i) {
            for(int k = 0; k < ncolor; ++k) {
                if(min_cost_color == k) tmp[k] = cost_so_far[second_min_cost_color] + costs[i][k];
                else tmp[k] = cost_so_far[min_cost_color] + costs[i][k];
            }
            //update min and second_min
            min_cost = INT_MAX, second_min_cost = INT_MAX;
            min_cost_color = 0, second_min_cost_color = 0;
            for(int k = 0; k < ncolor; ++k) {
                if(tmp[k] < min_cost) { 
                    second_min_cost = min_cost; second_min_cost_color = min_cost_color;
                    min_cost = tmp[k]; min_cost_color = k; 
                } else if(tmp[k] < second_min_cost) { 
                    second_min_cost = tmp[k]; second_min_cost_color = k;
                }
            }
            cost_so_far.swap(tmp);
        }
        return min_cost;        
    }
};
