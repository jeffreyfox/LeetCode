/*
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:

    All numbers (including target) will be positive integers.
    Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
    The solution set must not contain duplicate combinations.

For example, given candidate set 10,1,2,7,6,1,5 and target 8,
A solution set is:
[1, 7]
[1, 2, 5]
[2, 6]
[1, 1, 6]
*/

// Notice the difference between this and problem 039? Here it is "collection" while 039 is "set", which means that here C can have duplicates.

// Solution 1. Iterative solution. Similar to 039, except need to avoid choosing duplicates again, also should only choose one number once.
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int> > result;
        int n = candidates.size();
        if(n == 0) return result;
        sort(candidates.begin(), candidates.end());
        vector<int> tmp;
        dfs(candidates, 0, target, tmp, result);
        return result;
    }
    void dfs(vector<int>& candidates, int i, int target, vector<int>& tmp, vector<vector<int> >& result) {
        if(target == 0) {
            result.push_back(tmp);
            return;
        }
        int n = candidates.size();
        if(i == n || target < candidates[i]) return;
        tmp.push_back(0);
        //choose any number from i to n.
        for(int j = i; j < n; ++j) {
            if(j > i && candidates[j] == candidates[j-1]) continue; //avoid duplicates
            tmp.back() = candidates[j];
            dfs(candidates, j+1, target-candidates[j], tmp, result); //j+1: choose the number only once.
        }
        tmp.pop_back();
    }
};

// 2021.11
// Recursive solution.
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> tmp;
        sort(candidates.begin(), candidates.end());
        helper(candidates, 0, candidates.size(), target, &tmp, &result);
        return result;
    }
private:
    void helper(vector<int>& candidates, int beg, int end, int residue, vector<int> *tmp, vector<vector<int>> *result) {
        if (residue < 0) {
            return;
        }
        if (residue == 0) {
            result->push_back(*tmp);
            return;
        }
        for (int j = beg; j < end; ++j) {
            // Avoid duplicate combinations
            if (j > beg && candidates[j] == candidates[j-1]) continue;
            // pick candidates[j]
            tmp->push_back(candidates[j]);
            // Avoid picking the same number again
            helper(candidates, j+1, end, residue - candidates[j], tmp, result);
            tmp->pop_back();
        }
    }
};
