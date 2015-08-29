/*
 Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity. 
*/

// O(n) solution: use a hash table for O(1) look-up of each number.
// For each number, scan its left/right neighbors and count them, also remove found elements froms table.s

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> table;
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            table.insert(nums[i]);
        }
        int max_count = 0;
        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            if(table.count(x) == 0) continue;
            table.erase(x); //remove it
            int cnt = 1;
            while(table.count(--x)) { cnt++; table.erase(x); }
            x = nums[i];
            while(table.count(++x)) { cnt++; table.erase(x); }
            max_count = max(max_count, cnt);
        }
        return max_count;
    }
};
