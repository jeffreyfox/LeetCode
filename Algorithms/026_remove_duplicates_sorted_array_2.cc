class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if(n == 0) return 0;
   		int i(0), j(1);
		while(1) {
			while(j < n && A[j] == A[i]) j++;
			if(j == n) break;
			//num[j] is first element not equal to num[i]
			A[++i] = A[j++];
		}
		return i+1;   
    }
};
