/*
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue. 

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively. 

Note:
 You are not suppose to use the library's sort function for this problem. 

click to show follow up.


Follow up:
 A rather straight forward solution is a two-pass algorithm using counting sort.
 First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
*/

// Dutch national flag problem

class Solution {
public:
    void sortColors(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        // [0 .. lo-1] == 0, [lo, mid-1] == 1, [mid, hi] TBD, [hi+1, n-1] == 2 
        int lo = 0, mid = 0, hi = n-1;
        while(mid <= hi) {
            int x = nums[mid];
            if(x == 0) swap(nums[mid++], nums[lo++]);
            else if(x == 1) mid++;
            else swap(nums[mid], nums[hi--]);
        }
    }
};

