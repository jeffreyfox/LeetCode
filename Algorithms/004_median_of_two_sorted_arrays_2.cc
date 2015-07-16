class Solution {
public:
	double findMedianSortedArrays(int A[], int m, int B[], int n) {
		int k = (m+n)/2; 
		if((m+n)%2 == 0) { //even
			int a = Select(A, m, B, n, k);
			int b = Select(A, m, B, n, k+1);
			return double(a+b)/2.0;
		} else return Select(A, m, B, n, k+1); //odd
	}

	//Binary search algorithm to selelect k-th order statistics from two SORTED arrays. Average O(log(m+n)) time.
	int Select(int A[], int m, int B[], int n, int k) {
		int idx = SelectUtil(A, B, n, 0, m-1, k); //search in A
		if(m == 0) return B[k-1];
		else if(n == 0) return A[k-1];
		
		if(idx != -1) return A[idx];
		else {
			idx = SelectUtil(B, A, m, 0, n-1, k); //search in B
			return B[idx];
		}
	}
    
 	//Utility function to find k-th order static in A+B in A[l .. r], B's size is n
	int SelectUtil(int A[], int B[], int n, int l, int r, int k) {
		if(r < l) return -1;
		int m = (l+r)/2;
		int x = A[m];
		//x is <= m+1 elements in A, check if x is <= k-(m+1) elements in B
		int q = k-m-1;
		if(q < 0 || (q < n && x > B[q])) return SelectUtil(A, B, n, l, m-1, k); //search left (A[l .. m-1])
		if(q > n || (q > 0 && x < B[q-1])) return SelectUtil(A, B, n, m+1, r, k); //search right (A[m+1 .. r])
		if((q == 0 || x >= B[q-1]) && (q == n || x <= B[q])) return m;
	}
};
