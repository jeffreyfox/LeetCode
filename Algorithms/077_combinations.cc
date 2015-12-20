/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/

// Solution 1. Recursive solution. Start with k trials, every time decrement trials. Stop recursion when there is no trials left (k == 0). (12ms)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        dfs(1, n, k, tmp, result);
        return result;
    }
    //k trials left, start from number i, maximum is n
    void dfs(int i, int n, int k, vector<int>& tmp, vector<vector<int> >& result) {
        if(k == 0) {
            result.push_back(tmp);
            return;
        }
        if(i > n) return; //no numbers available
        int size = tmp.size();
        for(int j = i; j <= n; ++j) { //choose number between i and n
            tmp[size-k] = j; //choose number j
            dfs(j+1, n, k-1, tmp, result); //dfs starting with j+1
        }
    }
};

// Solution 2. Optimized recursive solution. Stop recursion after making the decision for the last trial (k == 1), also avoid uncessary trial when i > n.
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        dfs(1, n, k, tmp, result);
        return result;
    }
    //k trials left, start from number i, maximum is n
    void dfs(int i, int n, int k, vector<int>& tmp, vector<vector<int> >& result) {
        int size = tmp.size();
        for(int j = i; j <= n; ++j) { //choose number between i and n
            tmp[size-k] = j; //choose number j
            if(k == 1) result.push_back(tmp); //reaching the end
            else if(j < n) dfs(j+1, n, k-1, tmp, result); //dfs starting with j+1
        }
    }
};	

// Solution 3. Iterative. Save results at i == k. (16ms)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        int i = 0; 
        while(i >= 0) { //the i-th choice ( 0 <= i < k)
            if(i == k) { 
                result.push_back(tmp); 
                i--; //backtrace!
                continue; 
            }
            tmp[i]++; //choose the next number
            if(tmp[i] > n) { i--; continue; } //back trace
            i++; //go to next step
            if(i < k) tmp[i] = tmp[i-1]; //choose right starting point for the next tmp[i]++
        }
        return result;
    }
};

// Solution 3. Iterative, optmized and simpler. Save results at i == k-1. (8ms)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        int i = 0; 
        while(i >= 0) { //the i-th choice ( 0 <= i < k)
            tmp[i]++; //choose the next number
            if(tmp[i] > n) i--; //back trace
            else if (i == k-1) result.push_back(tmp);
            else {
                i++; //go to next step
                tmp[i] = tmp[i-1]; //choose right starting point for the next tmp[i]++
            }
        }
        return result;
    }
};

