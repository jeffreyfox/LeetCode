class Solution {
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        int k = (m+n)/2; 
        if((m+n)%2 == 0) {
            int a = Select(A, m, B, n, k);
            int b = Select(A, m, B, n, k+1);
            return double(a+b)/2.0;
        } else { //odd
            return Select(A, m, B, n, k+1);
        }
    }

	//Binary search algorithm to selelect k-th order statistics from two SORTED arrays. Average O(m+n) time.
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
		if(q < 0) return SelectUtil(A, B, n, l, m-1, k); //search left (A[l .. m-1])
		else if(q > n) return SelectUtil(A, B, n, m+1, r, k); //search right (A[m+1 .. r])
		else if(q == 0) {
			if(x <= B[q]) return m;
			else return SelectUtil(A, B, n, l, m-1, k);
		} else if (q == n) {
			if( x >= B[q-1]) return m;
			else return SelectUtil(A, B, n, m+1, r, k);
		} else {
			if(x >= B[q-1] && x <= B[q]) return m;
			else if (x > B[q]) return SelectUtil(A, B, n, l, m-1, k);
			else return SelectUtil(A, B, n, m+1, r, k);
		}
	}
};
