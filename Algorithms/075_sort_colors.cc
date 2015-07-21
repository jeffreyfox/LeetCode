// Dutch national flag problem

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int lo = 0, hi = n-1, i = 0;
        // invariant:
        // [0 .. lo-1] == 0
        // [lo .. i-1] == 1
        // [i .. hi] unchecked
        // [hi+1 .. n-1] == 2
        while (i <= hi) { //still there's element to be checked
            int v = nums[i];
            if (v == 0) swap(nums, i++, lo++);
            else if (v == 1) i++;
            else swap(nums, i, hi--);
        }
    }
    
    void swap(vector<int>& nums, int i , int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
};
