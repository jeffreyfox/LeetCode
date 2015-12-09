/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity. 
*/

/*
Solution 1. More elegant. Use a hash table for O(1) look-up of each number.
Then scan the array again. First check if element is in set, if not just continue (no need to search a previously erased element). For each entry, scan numbers to left and right to see if they are in the map, count total number of adjacent numbers. At the same time remove them to avoid future redundant search.
e.g. 0 1  3 4 5 6  8 9,
when 4 is found, scan and find 3 and 6, with count = 4, remove all elements from 3 to 6. so next time we see a 5, we won't count again.
*/

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

/*
Solution 2. use a map, storing the starting and ending position of each point.[ 2, 3, 4] : 2=>4, 4=>2, 3 does not matter.

For this to work under duplicated entries, we should not visit the same node again. Once it is in the map, do nothing. Otherwise it might mess up the result.

When inserting a new number, check its neighbors to see if there is any neighoring intervals. If there is an interval on the left, update the extreme points. Do the same for the right interval.
*/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return n;
        int max_len = 0;
        unordered_map<int, int> dict;
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            int left = x, right = x;
            if(dict.count(x)) continue; //avoid revisiting
            dict[x] = x;
            if(dict.count(x-1)) {
               left = dict[x-1];
               dict[left] = x;
               dict[x] = left;
            }
            if(dict.count(x+1)) {
               right = dict[x+1];
               dict[left] = right;
               dict[right] = left;
            }
            max_len = max(right-left+1, max_len);
        }
        return max_len;
    }
};

