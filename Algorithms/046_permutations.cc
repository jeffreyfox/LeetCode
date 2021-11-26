/*
Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1]. 
*/

// 2021.
// Solution using backtracking. Use a vector to track if each element has been used or not. An improved approach is to use bits to store used information.
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.empty()) return {};
        vector<int> tmp;
        vector<vector<int>> result;
        vector<bool> used(nums.size(), false);
        search(nums, nums.size(), used, tmp, result);
        return result;
    }
    // picking k numbers from unused numbers in |nums|.
    void search(const vector<int> &nums, int k, vector<bool> &used, vector<int> &tmp, vector<vector<int>> &result) {
        if (k == 0) {
            result.push_back(tmp);
            return;
        }
        tmp.push_back(0);
        for (int j = 0; j < nums.size(); ++j) {
            if (used[j]) continue;
            // pick j
            tmp.back() = nums[j];
            used[j] = true;
            search(nums, k-1, used, tmp, result);
            used[j] = false;
        }
        tmp.pop_back();
    }
};

// Solution 1. Use next permutation algorithm to print permutations in lexigraphical order (see 031)
// use a tag to indicate the status of permutation. If reaching the last permutation (descending order), return false. 
// Also works for cases when duplicated entries exist
// Caveats: 
// 1. If use a counter to print exactly n! permutations, then does not for cases where duplicated entries exist!
// 2. array should be sorted in the beginning!

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end()); //first sort the array!
        result.push_back(nums);
        while(nextPermutation(nums)) result.push_back(nums);
        return result;
    }
    bool nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = n-2, l = n-1;
        while(k >= 0 && nums[k] >= nums[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) return false;
        while(l > k && nums[l] <= nums[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(nums[k], nums[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(nums[i++], nums[j--]);
        return true;
    }
};

// Solution 2. Recursive solution using swapping. Does not work for duplicated cases. Developing a method that deals with duplicated cases are not straightforward, because the
// array order is destructed during the swapping! One hack is to introduce a table storing used elements, and avoid using them again in the same level of dfs search (see 047)
// Note that this method does not print the permutations in lexigraphical order!

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        dfs(nums, 0, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<vector<int> >& result) { 
        int n = nums.size();
        if(i == n) {
            result.push_back(nums);
            return;
        }
        for(int k = i; k < n; ++k) {
            swap(nums[i], nums[k]);
            dfs(nums, i+1, result);
            swap(nums[i], nums[k]);
        }
    }
};

// Solution 3. Recursive solution, each time take a number, use a bit status number indicating which number has been taken. Can be extended to duplicated cases (see 047).
// Some bit operators:
// checking if k-th number is used: if(state & (1 << k))
// set the tag for the k-th number: state |= (1 << k)
// unset the tag for the k-th number: state &= ~(1 << k)

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int state = 0; //bit states for 0 to n-1 
        int n = nums.size();
        vector<int> tmp(n, 0);
        dfs(nums, 0, tmp, result, state);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result, int state) {
        int n = nums.size();
        if(i == n) {
            result.push_back(tmp);
            return;
        }
        for(int k = 0; k < n; ++k) { //try all possible numbers
            if(state & (1 << k)) continue; //already used
            tmp[i] = nums[k]; //use nums[k]
            state |= (1 << k);
            dfs(nums, i+1, tmp, result, state);
            state &= ~(1 << k); //retrace
        }
    }
};

// Solution 4. An iterative solution using O(n) space to track the status of each number, and another O(n) space to record the positions of each number used.

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int n = nums.size(), i(0);
        vector<bool> used(n, false); //whether i-th number has been used
        vector<int> pos(n, -1); //position in nums for the number chosen for i-th position in permutation sequence
        while(i >= 0) { //check i-th position
            if(i == n) {
                vector<int> tmp(n, 0);
                for(int k = 0; k < n; ++k) tmp[k] = nums[pos[k]];
                result.push_back(tmp);
                i--; //retrace
                continue;
            }
            //find next unused number for i-th selection
            if(pos[i] >= 0) used[pos[i]] = false; //unset
            pos[i]++;
            while(pos[i] < n && used[pos[i]]) pos[i]++;
            if(pos[i] == n) { //no numbers left
                pos[i] = -1;
                i--; //retrace
                continue;
            }
            used[pos[i]] = true;
            //find next pos[i]
            i++;
        }
        return result;
    }
};


