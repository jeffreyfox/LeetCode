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
