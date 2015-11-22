/*
There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
*/

/*
Solution 1: compare medians of the two array.
We make a general algorithm that returns the k-th order value from two sorted arrays ( 0 <= k < m+n ). Then use it to calculate the median.
First some mathematics:
Generally, for an array nums[lo, hi], with length len = hi-lo+1, mid = (lo+hi)/2 = lo + ceil((hi-lo)/2.0). Let hlen = (hi-lo)/2. Thus, number of elements before mid (exclusive) is ceil((hi-lo)/2.0) = hlen, and number of elements after mid (exclusive) is floor((hi-lo)/2.0) which can be either hlen or hlen+1, depending on the length of array. Here we have used the fact that
for any integer: ceil(x/2.0) + floor(x/2.0) = x

Now we have two arrays nums1[lo1, hi1], nums2[lo2, hi2], we calculate mid1 and mid2 accordingly. We compare nums1[mid1] and nums2[mid2], say we have nums1[mid1] <= nums2[mid2]. If we combine the two in sorted order we will have something like:
      ... nums1[mid1] ... nums2[mid2] ...
From above, we know that:
a. nums1[mid1] has at least hlen1 + hlen2 + 1 (from nums1, nums2, and nums2[mid2] respectively) elements behind it (exlucsively)
b. nums2[mid2] has at least hlen1 + hlen2 + 1 elements ahead of it (exclusively)

Now let's check k's value, the k-th element (k starts from 0) has k elements before it,
1. if k <= hlen1 + hlen2, then the element can have at most hlen1+hlen2 elements ahead of it. Then we know for sure that the answer is before nums2[mid2], so we can discard nums2[mid2] and the elements in nums2 after it can be excluded
2. if k > hlen1 + hlen2, then the element can have at least hlen1+hlen2+1 elements ahead of it. Can we discard nums1[mid1] and the ones in nums1 ahead of it? Yes! Because nums1[mid1] will have 
at most hlen1 + hlen2 elements ahead of it, including nums1[mid1] we have hlen1+hlen2+1, which we can safely exclude mathemetically (in practice we only exclude elements nums1[0 .. mid1]). The calculation is below:
   number of elements before and including nums1[mid1] <= len1 + len2 - (hlen1 + hlen2 + 1)
                                                        = (hi1-lo1+1) + (hi2-lo2+1) - ( floor((hi1-lo1)/2.0) + floor((hi2-lo2)/2.0 + 1)
                                                        = ceil((hi1-lo1)/2.0) + ceil((hi2-lo2)/2.0) + 1
                                                        = hlen1 + hlen2 + 1
Similar for the case where nums1[mid1] > nums2[mid2]
*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int k = (m+n)/2;
        if((m + n) % 2 == 0) {
            int v1 = findKth(nums1, 0, m-1, nums2, 0, n-1, k-1);
            int v2 = findKth(nums1, 0, m-1, nums2, 0, n-1, k);
            return double(v1+v2)/2;
        } else {
            return findKth(nums1, 0, m-1, nums2, 0, n-1, k);
        }
    }
    int findKth(vector<int>& nums1, int lo1, int hi1, vector<int>& nums2, int lo2, int hi2, int k) {
        if(lo1 > hi1) return nums2[lo2+k];
        if(lo2 > hi2) return nums1[lo1+k];
        int mid1 = lo1 + (hi1-lo1)/2;
        int mid2 = lo2 + (hi2-lo2)/2;
        int hlen1 = mid1 - lo1, hlen2 = mid2 - lo2; //number of elements before mid
        if(nums1[mid1] <= nums2[mid2]) {
            if(k <= hlen1 + hlen2) return findKth(nums1, lo1, hi1, nums2, lo2, mid2-1, k); //drop elements after mid2 (inclusive)
            else return findKth(nums1, mid1+1, hi1, nums2, lo2, hi2, k-hlen1-1); //drop elements before mid1 (inclusive)
        } else {
            if(k <= hlen1 + hlen2) return findKth(nums1, lo1, mid1-1, nums2, lo2, hi2, k); //drop elements after mid1 (inclusive)
            else return findKth(nums1, lo1, hi1, nums2, mid2+1, hi2, k-hlen2-1); //drop elements before mid2 (inclusive)
        }
    }
};

// The same idea, iterative solutionclass Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int k = (m+n)/2;
        if((m + n) % 2 == 0) {
            int v1 = findKth(nums1, 0, m-1, nums2, 0, n-1, k-1);
            int v2 = findKth(nums1, 0, m-1, nums2, 0, n-1, k);
            return double(v1+v2)/2;
        } else {
            return findKth(nums1, 0, m-1, nums2, 0, n-1, k);
        }
    }
    int findKth(vector<int>& nums1, int lo1, int hi1, vector<int>& nums2, int lo2, int hi2, int k) {
        while(lo1 <= hi1 && lo2 <= hi2) {
            int mid1 = lo1 + (hi1-lo1)/2;
            int mid2 = lo2 + (hi2-lo2)/2;
            int hlen1 = mid1 - lo1, hlen2 = mid2 - lo2; //number of elements before mid
            if(nums1[mid1] <= nums2[mid2]) {
                if(k <= hlen1 + hlen2) hi2 = mid2-1; //drop elements after mid2 (inclusive)
                else { lo1 = mid1+1; k -= hlen1+1; } //drop elements before mid1 (inclusive)
            } else {
                if(k <= hlen1 + hlen2) hi1 = mid1-1;  //drop elements after mid1 (inclusive)
                else { lo2 = mid2+1; k -= hlen2+1; }  //drop elements before mid2 (inclusive)
            }
        }
        if(lo1 > hi1) return nums2[lo2+k];
        else return nums1[lo1+k];
    }
};

