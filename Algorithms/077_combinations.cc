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

// Solution 1. Recursive solution. We pick numbers from left to right and do not go back, e.g. 1, 2, 4, but not 1, 4, 2 (because they are the same combination). 
// Each time we track how many numbers are left to pick. There are two variations with different return condition.
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> tmp;
        combine(1, n, k, tmp, result);
        return result;
    }
    // Try to pick k numbers from i to n. tmp stores the partial results.
    // Variation 1, return when there are no numbers left to pick.
    void combine(int i, int n, int k, vector<int> &tmp, vector<vector<int>> &result) {
        if (k == 0) {
            result.push_back(tmp);
            return;
        }
        for (int j = i; j <= n; ++j) {
            tmp.push_back(j);            
            // pick k-1 numbers from j+1 to n
            combine(j+1, n, k-1, tmp, result);
            tmp.pop_back();
        }
    }
    // Variation 2. Return early to avoid unnecessary recursive calls.
    void combine(int i, int n, int k, vector<int> &tmp, vector<vector<int>> &result) {
        for (int j = i; j <= n; ++j) {
            tmp.push_back(j);
            if (k == 1) result.push_back(tmp); // Early return
            // pick k-1 numbers from j+1 to n
            else combine(j+1, n, k-1, tmp, result);
            tmp.pop_back();
        }
    };
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

// Solution 4. Iterative, optmized and simpler. Save results at i == k-1. (8ms)
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

// 2021.11
// Solution 5. Recursive. Reuse intermediate vector instead of copying.
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> path;
        path.reserve(k);
        combine_helper(1, n, k, &path, &result);
        return result;
    }
    
private:
    // Pick |num_left| numbers from [beg, end]. |path| is the partially constructed result.
    // If |num_left| equals 0 it means no numbers to pick and we add the path to the result.
    void combine_helper(int beg, int end, int num_left, vector<int> *path, vector<vector<int>> *result) {
        if (num_left == 0) {
            result->push_back(*path);
            return;
        }
        for (int j = beg; j <= end; ++j) {
            // pick j
            path->push_back(j);
            // Can further optimize to append path to the result here if num_left = 1.
            combine_helper(j+1, end, num_left - 1, path, result);
            path->pop_back();
        }
    }
};
