/*
Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.

Note: If there are several possible values for h, the maximum one is taken as the h-index.

Hint:

An easy approach is to sort the array first.
What are the possible values of h-index?
A faster approach is to use extra space.
*/

// Solution using binary search. First sort array in descending order. Then find the largest index i such that nums[i] >= i+1.

class Solution {
public:
    int hIndex(vector<int>& citations) {
        if(citations.empty()) return 0;
        sort(citations.begin(), citations.end(), std::greater<int>());
        int n = citations.size();
        int lo = 0, hi = n-1;
        //[0 .. lo-1]: num[i] >= i+1; [hi+1, n): num[i] < i+1, return hi
        while(lo <= hi) {
            int mid = lo + (hi-lo)/2;
            if(citations[mid] >= mid+1) lo = mid+1;
            else hi = mid-1;
        }
        return hi+1;
    }
};
