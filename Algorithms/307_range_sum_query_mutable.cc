/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
The update(i, val) function modifies nums by updating the element at index i to val.

Example:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8

Note:

    The array is only modifiable by the update function.
    You may assume the number of calls to update and sumRange function is distributed evenly.
*/

// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.update(1, 10);
// numArray.sumRange(1, 2);

// Solution using binary indexed tree, find and update both O(logn).
// A little tricky in update function. Need to calculate the difference between current value and old value.
// Also uses 1-based indexing, so need to take care of the offset.

class NumArray {
public:
    NumArray(vector<int> &nums) {
        n = nums.size(); //0 is dummy node
        bitsum.resize(n+1, 0);
        num.resize(n+1, 0);
        for(int i = 0; i < n; ++i) {
           update(i, nums[i]); //i is index in nums
        }
    }

    int sumRange(int i, int j) {
        if(i > j || i < 0 || j >= n) return 0;
        if(i == j) return num[i+1];
        return getSum(j) - getSum(i-1);
    }

    void update(int i, int val) {
        int error = val - num[++i];
        num[i] = val;
        while(i <= n) {
            bitsum[i] += error;
            i += (i & (-i)); 
        }
    }
private:
    //accumulated sum from nums[0 .. i]
    int getSum(int i) {
        if(i < 0 || i >= n) return 0;
        i++;
        int sum = 0;
        while(i > 0) {
            sum += bitsum[i];
            i -= (i & (-i));
        }
        return sum;
    }
    vector<int> num;
    vector<int> bitsum;
    int n;
};

