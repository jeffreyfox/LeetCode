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

// 2021. Solution using the idea of counting sort. The only difference is in step 2 when accumulating counts, we need to start from right and move backwards. 
// This is due to the definition of the H-index.
// Can optimize and merge step 3 and step 2 into a single loop.
// Also, the size of the counting matrix doesn't need to be kMax. Only citations.size() + 1 is enough (again due to the definition of the H-index).
class Solution {
public:
    int hIndex(vector<int>& citations) {
        vector<int> counts(kMax);
        // Build counts
        for (const auto c : citations) {
            counts[c] ++;
        }
        // Accumulate counts
        for (int j = kMax - 2; j >= 0; --j) {
            counts[j] += counts[j+1];
        }
        // Search counts
        int result = 0;
        for (int j = 0; j < kMax; ++j) {
            if (counts[j] >= j) result = j;
            else break;
        }
        return result;
    }
private:
    const int kMax = 1001;
};

// 2015.
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

// Solution 2. Use another table to store the counts, O(n) space, but O(n) time.
// dict[i] stores the number of papers that have citation of i, since hindex can only be 0 to n, where n is the size of input array,
// we only need to keep track of the counts for i = 0 .. n, hence the size of dict is n+1.

class Solution {
public:
    int hIndex(vector<int>& citations) {
        if(citations.empty()) return 0;
        int n = citations.size();
        vector<int> dict(n+1, 0); //dict[i]: count for citations equal to i
        for(auto c: citations)  dict[min(c, n)]++;
        for(int i = n, tot = 0; i >= 0; i--) {
            tot += dict[i];
            if(tot >= i) return i;
        }
        return 0;
    }
};
