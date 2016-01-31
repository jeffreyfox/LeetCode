/*
Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.
*/

// Maintain a window, when searching, utilize the ordered feature of set, and find the element >= a given value in O(lgn) time. 

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int n = nums.size();
        for(int i = 0; i < n; i++) { //try element i
            if(i > k) dict.erase(nums[i-k-1]); //remove older elements
            long x = nums[i];
            auto it = dict.lower_bound(x - t); //find first element >= x-t in the window
            if(it != dict.end() && *it <= x + t) return true; //found and value <= x+t
            dict.insert(x); //insert to window
        }
        return false;
    }
    set<long> dict; //ordered-set for fast search
};
