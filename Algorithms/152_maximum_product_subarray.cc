/*
Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6. 
*/

// DP solution.
// Keep track of maximum (in terms of absolute value) positive and negative values (initially set as 0)
// Update the values based on the polarity of newly seen element. If max_pos_prod and max_neg_prod are 0, then they are considered uninitialized.
// Caveat: When updating max_pos and max_neg, need to use temporary variables
// Optimization: since we call nums[i] multiply times, save it into a variable x to avoid excessive array indexing cost.

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int max_pos_prod = 0, max_neg_prod = 0, max_prod = INT_MIN;
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if(x == 0) {
                max_prod = max(max_prod, 0);
                max_pos_prod = max_neg_prod = 0;
            } else if(x > 0) {
                max_pos_prod = (max_pos_prod > 0) ? max_pos_prod*x : x;
                max_neg_prod = (max_neg_prod < 0) ? max_neg_prod*x : 0;
            } else { //nums[i] < 0
                int tmp_pos = max_pos_prod, tmp_neg = max_neg_prod;
                max_pos_prod = (tmp_neg < 0) ? tmp_neg*x : 0;
                max_neg_prod = (tmp_pos > 0) ? tmp_pos*x : x;
            }
            if(max_pos_prod > 0 && max_prod < max_pos_prod) max_prod = max_pos_prod;
            if(max_neg_prod < 0 && max_prod < max_neg_prod) max_prod = max_neg_prod; //needed for n=1 case with one negative number (max_pos undefined)
        }
        return max_prod;
    }
};

// A slightly different solution, considering n=1 corner case explicitly (so that max_pos will always be valid)
// Corner case: when there is only one negative number, should return itself, not 0.

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0]; //corner case
        int max_pos(0), max_neg(0), max_prod(0);
        int tmp_pos(0), tmp_neg(0);
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if(x == 0) tmp_pos = tmp_neg = 0;
            else if (x > 0) {
                tmp_pos = (max_pos > 0) ? max_pos*x : x;
                tmp_neg = (max_neg < 0) ? max_neg*x : 0;
            } else {  //x < 0
                tmp_pos = (max_neg < 0) ? max_neg*x : 0;
                tmp_neg = (max_pos > 0) ? max_pos*x : x;
            }
            max_pos = tmp_pos; max_neg = tmp_neg;
            max_prod = max(max_prod, max_pos);
        }
        return max_prod;
    }
};
