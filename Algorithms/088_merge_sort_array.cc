/*
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.
*/

// Best solution: start backwards, utilize the extra space after nums1, only O(1) extra space needed.
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, k = m+n-1;
        while(i >= 0 || j >= 0) {
            if(j < 0) break;
            else if(i < 0) nums1[k--] = nums2[j--];
            else nums1[k--] = nums1[i] <= nums2[j] ? nums2[j--] : nums1[i--];
       }
    }
};

// A slightly more concise solution
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, k = m+n-1;
        while(j >= 0) {
            nums1[k--] = (i < 0 || nums1[i] <= nums2[j]) ? nums2[j--] : nums1[i--];
       }
    }
};

// An old solution: merge procedure in merge sort. No sentinel. Need extra array of length O(m+n).

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int tot = m+n;
        vector<int> aux(tot, 0);
        for (int i = 0, j = 0, k = 0; i < m || j < n; ) {
            int v1 = (i < m) ? nums1[i] : INT_MAX;
            int v2 = (j < n) ? nums2[j] : INT_MAX;
            if (v1 < v2) { aux[k++] = v1; i++; }
            else { aux[k++] = v2; j++; }
        }
        for (int i = 0; i < tot; ++i) nums1[i] = aux[i];
    }
};
