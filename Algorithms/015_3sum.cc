/*
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

    Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
    The solution set must not contain duplicate triplets.

    For example, given array S = {-1 0 1 2 -1 -4},

    A solution set is:
    (-1, 0, 1)
    (-1, -1, 2)
*/

/// O(n2) solution
/// Need to consider duplicated entries.
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() <= 2) return {};
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            // pick j and k from nums[i+1.. n-1]
            int j = i+1, k = n-1;
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                if (sum == 0) result.push_back({nums[i], nums[j], nums[k]});
                if (sum < 0) {
                    do { j++; } while (j < n && nums[j] == nums[j-1]);
                } else {
                    do { k--; } while (k >= 0 && nums[k] == nums[k+1]);
                }                    
            }
        }
        return result;
    }
};

/// O(n2 lgn) solution. Iterate first 2 brute-force, and use binary search to find 3rd element.
/// Need to avoid duplicated entries. (lines 14 and 16).

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ret;
        
        int n = nums.size();
        if(n <= 2) return ret;
        vector<int> sol(3, 0);
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; ++i) { //whether nums[i] is one of the triplet?
            if(i > 0 && nums[i] == nums[i-1]) continue; //ignore duplicates
            for(int j = i+1; j < n; ++j) {
                if(j > i+1 && nums[j] == nums[j-1]) continue; //ignore duplicates
                int target = -(nums[i] + nums[j]);
                int r = find(nums, j+1, target);
                if(r != -1) {
                    sol[0] = nums[i], sol[1] = nums[j], sol[2] = nums[r];
                    ret.push_back(sol);
                }
            }
        }
        return ret;
    }
    
    //search target in sorted array nums[k..end)
    int find(vector<int>& nums, int k, int target) {
        int lo = k, hi = nums.size()-1;
        while(lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if(target < nums[mid]) hi = mid-1;
            else if(target > nums[mid]) lo = mid+1;
            else return mid;
        }
        return -1;
    }
};
