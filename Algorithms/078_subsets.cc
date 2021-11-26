/*
Given a set of distinct integers, nums, return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/

// Solution 1. Recursive backtracking. Fan-out is 2 (for each number, add or not add).

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        search(nums, 0, tmp, result);
        return result;
    }
    // Generating subsets from nums[i, n).
    void search(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        if(i == nums.size()) {
            result.push_back(tmp);
            return;
        }
        // not taking nums[i]
        search(nums, i+1, tmp, result);
        // taking nums[i]
        tmp.push_back(nums[i]);
        search(nums, i+1, tmp, result);
        tmp.pop_back(); // backtrack
    }
};

// Solution 2. Recursive backtracking using DFS. Fan-out is number of unused elements, less tree depth and thus better efficiency than 1.

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > result;
        vector<int> tmp;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        result.push_back(tmp);
        for(int j = i; j < nums.size(); ++j) { //choose one from unused numbers
            tmp.push_back(nums[j]);
            dfs(nums, j+1, tmp, result);
            tmp.pop_back();
        }
    }
};

// Solution 3. Using cascading.
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        result.push_back({});
        // incrementally add an element in nums to the existing sets
        for (const int i : nums) {
            int size = result.size();
            for (int j = 0; j < size; ++j) {
                result.push_back(result[j]);
                result.back().push_back(i);
            }
        }
        return result;
    }
};

// Solution 4. Use bit operation. There are pow(2, n) results, we can label them in a consistent order similar to Solution 3.
// for example [1,2,3]:
// subset:       [], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]
// id(base 10):  0    1    2      3     4     5       6         7
// id(base 2):  000  001  010    011   100   101     110       111
// As we can see, number 1 (the 0-th number) only appears when last digit is set. number 2 (the 1st number) only appears when second from last digit is set, and so on. Thus, for each id, we can check which digit are set, and add the corresponding number to the subset.
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int size = 1 << n;
        sort(nums.begin(), nums.end());
        vector<vector<int> > result(size, vector<int>());
        for(int i = 0; i < result.size(); ++i) {
            for(int j = 0; j < n; ++j) {
                if(i & (1 << j)) result[i].push_back(nums[j]);
            }
        }
        return result;
    }
};

