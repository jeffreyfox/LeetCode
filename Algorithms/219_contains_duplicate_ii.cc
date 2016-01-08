/*
Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k. 
*/

// Solution 1. use a set to store the already seen elements. Maintain a sliding window of side k+1, when seeing a new element, remove the one that falls out of the window from the set. O(k) space. 28ms.
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> dict;
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            if(i > k) dict.erase(nums[i-k-1]);
            if(dict.count(nums[i])) return true;
            dict.insert(nums[i]);
        }
        return false;
    }
};

// Solution 2. Use a map to store the elements and its position. O(n) space. 32ms.

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> dict;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int v = nums[i];
            unordered_map<int, int>::iterator it = dict.find(v);
            if (it == dict.end()) dict[v] = i; //init last position
            else if (i - it->second <= k) return true; //found!
            else it->second = i; //update last position
        }
        return false;
    }
};

