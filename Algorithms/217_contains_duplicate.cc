/*
Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct. 
*/

// Solution 1. Use a set to store elements seen so far. O(n) space. O(n) time amortized.

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> dict;
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            if(dict.count(nums[i])) return true;
            dict.insert(nums[i]);
        }
        return false;
    }
};


// Solution 2. Presort the array, then do a linear search. O(1) space, O(nlgn) time. 

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 0; i < n-1; ++i) {
            if(nums[i] == nums[i+1]) return true;
        }
        return false;
    }
};
