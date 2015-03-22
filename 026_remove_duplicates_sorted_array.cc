class Solution {
public:
	int removeDuplicates(int A[], int n) {
		if(n == 0) return 0;
		int i(0), j(1), prev = INT_MAX;
		for(j = 0; j < n; ++j) {
			if(A[j] != prev) {
				A[i++] = A[j]; prev = A[j];
			}
		}
		return i;   
	}
};
