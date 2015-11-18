/*
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length. 
*/

// Solution: two pointers. 
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return n;
        int len = 0;
        int i = 0, j = 0;
        while(i < n) {
            j = i+1;
            while(j < n && nums[j] == nums[i]) j++;
            if(j >= i+1) nums[len++] = nums[i];
            if(j > i+1) nums[len++] = nums[i];
            i = j;
        }
        return len;
    }
};

// A old solution
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if(n == 0) return 0;
   		int i(0), j(1), prev = INT_MAX, count = 0;
		for(j = 0; j < n; ++j) {
		    if(A[j] == prev) count++;
		    else count = 1;
		    prev = A[j];
		    if(count <= 2) A[i++] = A[j]; 
		}
		return i;   
    }
};
