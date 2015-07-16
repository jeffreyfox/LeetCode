class Solution {
public:
	//O(n) solution with dynamic programming
	int maxSubArray(int A[], int n) {
		int max_ending_here = 0;
		int max_all = INT_MIN;
		for(int j = 0; j < n; ++j) { //check sub-array ending at arr[j]
		    if(max_ending_here > 0) {
				max_ending_here += A[j]; //use subarray arr[i..j]
			} else {
				max_ending_here = A[j]; //use subarray arr[j] only
			}
			//update sol if found a new max
			if(max_ending_here > max_all) max_all = max_ending_here;
		}        
		return max_all;
	}
};
