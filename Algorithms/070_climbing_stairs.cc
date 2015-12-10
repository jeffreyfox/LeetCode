/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top? 
*/

/// Fibonacci series, dynamic programming (bottom-up)
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        vector<int> sol(n+1, 0);
        sol[1] = 1; sol[2] = 2;
        for (int i = 3; i <= n; ++i)
            sol[i] = sol[i-1] + sol[i-2];
        return sol[n];    
    }
};

// Space optimized version. Only need value for the last 2 steps.
class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2) return n;
        int curr = 0, last = 2, last_last = 1;
        for(int i = 2; i < n; ++i) {
            curr = last + last_last;
            last_last = last;
            last = curr;
        }
        return curr;
    }
};

