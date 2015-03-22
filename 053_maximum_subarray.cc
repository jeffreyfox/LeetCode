class Solution {
public:
	//divide and conquer
	int maxSubArray(int A[], int n) {
		return maxSubArrayUtil(A, 0, n-1);
	}

	int maxSubArrayUtil(int A[], int p, int r) {
		if(r == p) return A[p]; //maxSum = arr[p]
		else {
			int q = p + (r-p)/2;
			int solL = maxSubArrayUtil(A, p, q); //left
			int solR = maxSubArrayUtil(A, q+1, r); //right
			int solC = maxCrossingArray(A, p, q, r); //crossing
			if(solL > solR) return solL > solC ? solL : solC;
			else return solR > solC ? solR : solC;
		}
	}

	//maximum subarray of arr[p..r] and crossing arr[q]
	int maxCrossingArray(int A[], int p, int q, int r) {
		int sum(0);
		int maxSumL(0), maxSumR(0);
		//left
		sum = 0;
		for(int i = q-1; i >= p; --i)  {
			sum += A[i];
			if(sum > maxSumL) maxSumL = sum;
		}
		//right 
		sum = 0;
		for(int i = q+1; i <= r; ++i)  {
			sum += A[i];
			if(sum > maxSumR) maxSumR = sum;
		}
		return maxSumL+maxSumR+A[q];
	}
};
