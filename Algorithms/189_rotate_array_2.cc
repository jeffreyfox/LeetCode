/*
Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.

[show hint]
Hint:
Could you do it in-place with O(1) extra space?

Related problem: Reverse Words in a String II
*/

// Juggling method (do-while loop)
// Need to get gcd of two numbers

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k = k % n;
        if(k == 0) return;
        for(int i = 0; i < gcd(n, k); ++i)
            rotate(nums, i, k);
    }
    //start from i, jump every step steps
    void rotate(vector<int>& nums, int i, int step) {
        int n = nums.size();
        int tmp = nums[i+n-step];
        int j  = i;
        do {
            swap(nums[j], tmp);
            j = (j+step) % n;
        } while (j != i);
    }
    void swap(int& i, int& j) {
        int t = i;
        i = j;
        j = t;
    }
    int gcd(int i, int j) {
        //make sure i >= j
        if(i < j) return gcd(j, i);
        if(j == 0) return i;
        return gcd(j, i-j);
    }
};
