/*
Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/

// Solution 1. Similar to #78 with recursive backtracking. We first sort the vector. Then for each number of occurrence K, we decide whether to pick it 0 times to K times.
// 0 times means not picking the number. So the fan-out for each decision tree root is K+1 instead of 2 in the previous case.
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> tmp;
        sort(nums.begin(), nums.end());
        search(nums, 0, tmp, result);
        return result;
    }
    // Generating subsets from nums[i, n).
    void search(const vector<int>& nums, int i, vector<int>& tmp, vector<vector<int>> &result) {
        if (i >= nums.size()) {
            result.push_back(tmp);
            return;
        }
        // j is the fist item whose value is not equal to nums[i]
        int j = i+1;
        while (j < nums.size() && nums[j] == nums[i]) j++;
        int num_dup = j - i; // number of duplicates
        // do not pick nums[i]
        search(nums, j, tmp, result);
        
        // pick nums[i] 1 to num_dup times
        for (int k = 1; k <= num_dup; ++k) {
            tmp.push_back(nums[i]);
            search(nums, j, tmp, result);            
        }
        // backtrack
        for (int k = 1; k <= num_dup; ++k) {
            tmp.pop_back();
        }        
    }
};

// Solution 2. Similar to #78, DFS backtracking with fan-out = number of unused elements
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        vector<int> tmp;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        result.push_back(tmp);
        for(int j = i; j < nums.size(); ++j) {
            if(j == i || nums[j] != nums[j-1]) { //ignore duplicates
                tmp.push_back(nums[j]);
                dfs(nums, j+1, tmp, result);
                tmp.pop_back();
            }
        }
    }
};

// Solution 3. Similar to #78, cascading.
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result;
        result.push_back({});
        sort(nums.begin(), nums.end());
        // for each element of occurrence n, incrementally add 1 to n of it to the existing set
        for (unsigned int i = 0; i < nums.size(); ) {
            int j = i+1;
            while (j < nums.size() && nums[j] == nums[i]) j++;
            int num_dup = j-i;
            // add 1 to num_dup nums[i] to the existing set            
            int size = result.size();
            for (int k = 1; k <= num_dup; ++k) {
                for (int l = (k-1)*size; l < k*size; ++l) {
                    result.push_back(result[l]);
                    result.back().push_back(nums[i]);
                }
            }
            i = j;
        }
        return result;
    }
};

