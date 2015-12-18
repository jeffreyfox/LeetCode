/*
Given an array and a value, remove all instances of that value in place and return the new length.

The order of elements can be changed. It doesn't matter what you leave beyond the new length. 
*/

// Solution 1, fastest. Just maintain two pointers. Since we don't care about elements == val, we don't use fancy color sort algorithms.

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if(nums.empty()) return 0;
        int i(0), j(0), n = nums.size();
        for(int j = 0; j < n; ++j) {
            if(nums[j] != val) nums[i++] = nums[j];
        }
        return i;
    }
};

// Solution 2, two color sort.
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        //[0 .. i-1] != val, [i, j-1] == val, [j, n-1] TBD
        if(nums.empty()) return 0;
        int i = 0, j = 0, n = nums.size();
        while(j < n) {
            if(nums[j] == val) j++;
            else swap(nums[j++], nums[i++]);
        }
        return i;
    }
};

// Solution. variation of solution 2.
/// Similar to two-color problem, use two pointers i, and j. Loop invariant:
/// 1. nums[0 .. i-1] != val
/// 2. nums[i .. j] to be determined
/// 3. nums[j .. end) == val
/// when i and j cross, return i

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int i = 0, j = nums.size()-1;
        while (i <= j) {
            if (nums[i] != val) i++;
            else swap(nums[i], nums[j--]);
        }
        return i;
    }
};

