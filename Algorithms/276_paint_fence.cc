/*
There is a fence with n posts, each post can be painted with one of the k colors.

You have to paint all the posts such that no more than two adjacent fence posts have the same color.

Return the total number of ways you can paint the fence.

Note:
n and k are non-negative integers. 
*/

//Solution: dynamic programming, keep counts for two cases: last two colors are same, and different.

class Solution {
public:
    int numWays(int n, int k) {
        if(n == 0 || k == 0) return 0;
        if(n == 1) return k;
        if(n == 2) return k*k;
        int last_two_same = k, last_two_diff = k*(k-1);
        for(int i = 3; i <= n; ++i) {
            int tmp = last_two_diff;
            last_two_diff = (last_two_same+last_two_diff)*(k-1);
            last_two_same = tmp;
        }
        return last_two_same + last_two_diff;
    }
};
