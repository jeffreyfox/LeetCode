/*
The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.
-2 (K) 	-3 	3
-5 	-10 	1
10 	30 	-5 (P)

Notes:

    The knight's health has no upper bound.
    Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.
*/

/*
Standard dynamic programming. Start from end and scan backwards, calculate the minimum points required at each position.DP solution. Retrace back to top left.
As starting point, set the right and bottom neighbor of P's cell to 1.

  dp[i][j]  | dp[i][j+1]
  _ _ _ _ _ | _ _ _ _ _ _ 
            |
 dp[i+1][j] |  

dp[i][j] stores the minimum points required at position [i][j] in order to reach the princess. We can reach pos[i][j] in two ways, from position [i-1][j] and position [i][j-1], and we can go from the place requiring minimum points. The points required at dp[i-1][j] is simply dp[i][j] - dungeon[i][j], and at least 1, so we have:
dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1])-dungeon[i][j]).
At the boundary, i = m-1 or j = n-1, we replace min by only one of the two neighbors.
At the princess point, we have dp[m-1][n-1] = 1-dungeon[m-1][n-1].
We can use sentinel nodes at the boundary, where all the sentinel values are INT_MAX, but for dp[m-1][n-1] to fit in the formula, we can set dp[m][n-1] and dp[m-1][n] as 1.	

Another solution is to start scanning from top left, but we need to store to variables for each position: the maximum points required at start in order to reach here, and the remaining points at this position.
*/

class Solution {
public:
    int calculateMinimumHP(vector<vector<int> >& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        vector<vector<int> > minHP(m+1, vector<int>(n+1, INT_MAX));
        minHP[m-1][n] = minHP[m][n-1] = 1; //this is the trick!
        for (int i = m-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                minHP[i][j] = max(1, min(minHP[i+1][j], minHP[i][j+1])-dungeon[i][j]);
            }
        }
        return minHP[0][0];
    }
};

/* Same idea as Solution 1 but space optimized */

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        vector<int> dp(n, INT_MAX);
        dp[n-1] = max(1, 1-dungeon[m-1][n-1]);
        //for last row (i == m-1)
        for(int j = n-2; j >= 0; j--)
            dp[j] = max(1, dp[j+1]-dungeon[m-1][j]);

        for (int i = m-2; i >= 0; i--) {
            dp[n-1] = max(1, dp[n-1]-dungeon[i][n-1]);
            for (int j = n-2; j >= 0; j--) {
                dp[j] = max(1, min(dp[j], dp[j+1])-dungeon[i][j]);
            }
        }
        return dp[0];
    }
};


