/*
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1]. 
*/

// Solution 1. Use next permutation algorithm to print permutations in lexigraphical order (see 031)
// Copied from 046_permutation.cc

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end());
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

// Solution 2. Recursive solution with swapping adapted from 046_permutations.cc. 
// To deal with duplicated entries, we can't use something simpler such as checking current to be exchanged ia equal to previously exchanged one, because the subarray maybe unsorted, for example, given aabbccd, and after a while we have bcd|caba, and the second part is unsorted. 
// Unless using a set structure, there is no way of preventing 'c' to be swapped with second 'a', because the previous is a 'b'.

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        dfs(nums, 0, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<vector<int> >& result) {
        int n = nums.size();
        if(i == n) {
            result.push_back(nums);
            return;
        }
        unordered_set<int> used;
        for(int k = i; k < n; ++k) {
            if(used.count(nums[k])) continue; //ignore duplicates that are already used
            used.insert(nums[k]); //insert to used table
            swap(nums[i], nums[k]);
            dfs(nums, i+1, result);
            swap(nums[i], nums[k]);
        }
    }
};

// Solution 3. Recursive solution adapted from Solution 3 in 046_permutations.cc. using a bit number representing status. Adapted to duplicated cases. Use a number "last" to store the last number used. When scanning forwards, skip the numbers equal to last as well.

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int state = 0; //bit states for 0 to n-1 
        int n = nums.size();
        sort(nums.begin(), nums.end());
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
        int last = INT_MIN; // assume no numbers are INT_MIN
        for(int k = 0; k < n; ++k) { //try all possible numbers
            if((state & (1 << k)) || nums[k] == last) continue; //already used, or duplicate entries
            last = tmp[i] = nums[k]; //use nums[k]
            state |= (1 << k);
            dfs(nums, i+1, tmp, result, state);
            state &= ~(1 << k); //retrace
        }
    }
};

// Solution 4. An iterative solution. Similar to that of 046_permutations. Only difference is that when we scan forward, if we see a used character OR a character that is the same as previous one, then we continue searching.
// A tricky case is when there is no previous character. So need to carefully write the conditiont in while loop.

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int n = nums.size(), i(0);
        sort(nums.begin(), nums.end()); //first sort array
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
            int tmp_pos = pos[i];
            pos[i]++;
            while(pos[i] < n && (used[pos[i]] || (tmp_pos >= 0 && nums[pos[i]] == nums[tmp_pos]))) pos[i]++;
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

