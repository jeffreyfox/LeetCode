/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:

Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3

Note:

    You may assume that the array does not change.
    There are many calls to sumRange function.
*/

// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);

// Since array is immutable, use standard DP. Use an array storing the partial sums. Array has an additional entry in the front storing "0".

class NumArray {
public:
    NumArray(vector<int> &nums) {
        n = nums.size();
        sum.resize(n+1, 0);
        for(int i = 0; i < n; ++i)
            sum[i+1] = sum[i] + nums[i];
    }

    int sumRange(int i, int j) {
        if(i < 0 || i >= n || j < 0 || j > n || i > j) return 0;
        return sum[j+1] - sum[i];
    }
    vector<int> sum; //partial sums
    int n;
};

// Another solution also storing the nums array itself, and optimized for i == j case.

class NumArray {
public:
    NumArray(vector<int> &nums) {
        n = nums.size();
        sum.resize(n+1, 0);
        val.resize(n+1, 0);
        for(int i = 0; i < n; ++i) {
            sum[i+1] = sum[i] + nums[i];
            val[i+1] = nums[i];
        }
    }

    int sumRange(int i, int j) {
        if(i < 0 || i >= n || j < 0 || j > n || i > j) return 0;
        if(i == j) return val[i+1];
        else return sum[j+1] - sum[i];
    }
    vector<int> sum; //partial sums
    vector<int> val; //values
    int n;
};

