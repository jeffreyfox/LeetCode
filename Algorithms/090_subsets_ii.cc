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

// Solution 1. Similar to #78, DFS backtracking with fan-out = 2.
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        if(i == nums.size()) {
            result.push_back(tmp);
            return;
        }
        int j = i;
        while(j < nums.size() && nums[j] == nums[i]) j++;
        //j is index of first element != nums[i], or end
        //not adding nums[i] to set
        dfs(nums, j, tmp, result);
        //adding 1 to j-i nums[i] to set
        for(int k = 0; k < j-i; ++k) {
            tmp.push_back(nums[i]);
            dfs(nums, j, tmp, result);
        }
        //revert back
        for(int k = 0; k < j-i; ++k) {
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

// Solution 3. Similar to #78, dynamic programming.
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        result.push_back(vector<int>()); //empty set
        int i = 0;
        int n = nums.size();
        while(i < n) {
            int j = i;
            while(j < n && nums[j] == nums[i]) j++;
            int ndup = j-i; //number of duplicates
            //add 1 - ndup nums[i] to existing solution
            int size = result.size();
            for(int k = 0; k < ndup; ++k) {
                for(int l = k*size; l < (k+1)*size; ++l) {
                    result.push_back(result[l]);
                    result.back().push_back(nums[i]);
                }
            }
            i = j;
        }
        return result;
    }
};

