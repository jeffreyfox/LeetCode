/*
Given an array of integers nums, sort the array in ascending order.

Example 1:

Input: nums = [5,2,3,1]
Output: [1,2,3,5]

Example 2:

Input: nums = [5,1,1,2,0,0]
Output: [0,0,1,1,2,5] 

Constraints:

    1 <= nums.length <= 5 * 104
    -5 * 104 <= nums[i] <= 5 * 104
*/

// Solution using top-down mergesort. Time complexity O(nlgn). Space compexity O(n) from the auxiliary vector to hold intermediate result.
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        msort(nums, 0, nums.size()-1);
        return nums;
    }
    
    void msort(vector<int>& nums, int l, int r) {
        if (r <= l) return;
        int m = (l + r) / 2;
        msort(nums, l, m);
        msort(nums, m+1, r);
        merge(nums, l, m, r);
    }
    
    // merges two sorted vectors: nums[l .. m] and nums[m+1 .. r]
    void merge(vector<int>& nums, int l, int m, int r) {
        vector<int> result(r-l+1);
        for (int i = l, j = m+1, k = 0; i <= m || j <= r; ) {
            if (i > m) result[k++] = nums[j++];
            else if (j > r) result[k++] = nums[i++];
            else if (nums[i] <= nums[j]) result[k++] = nums[i++];
            else result[k++] = nums[j++];
        }
        // copy result back to nums
        for (int k = l; k <= r; ++k) {
            nums[k] = result[k-l];
        }
    }
};

// Solution using bottom-up merge sort. Time complexity O(nlgn). Space complexity O(n) from the auxiliary vector to hold intermediate result.
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return nums;
        // bottom up.
        for (int len = 1; len < n; len *= 2) {
            for (int i = 0; i + len < n; i = i + 2*len) {
                merge(nums, i, i+len-1, min(i+2*len-1, n-1));
            }
        }
        return nums;
    }
  
    // merges two sorted vectors: nums[l .. m] and nums[m+1 .. r]
    void merge(vector<int>& nums, int l, int m, int r) {
        vector<int> result(r-l+1);
        for (int i = l, j = m+1, k = 0; i <= m || j <= r; ) {
            if (i > m) result[k++] = nums[j++];
            else if (j > r) result[k++] = nums[i++];
            else if (nums[i] <= nums[j]) result[k++] = nums[i++];
            else result[k++] = nums[j++];
        }
        // copy result back to nums
        for (int k = l; k <= r; ++k) {
            nums[k] = result[k-l];
        }
    }
};

// Solution using quicksort with randomized pivot. Time complexity O(nlgn). Space complexity O(lgn) from the recursion stack.
// Two partition methods are provided.
// Caveat: if not using randomlized pivot, the sorting with time out for an example with an already-sorted large array.
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        if (nums.empty() || nums.size() == 1) return nums;
        quickSort(nums, 0, nums.size()-1);
        return nums;
    }
    void quickSort(vector<int>& nums, int l, int r) {
        if (r <= l) return;
        int q = partition1(nums, l, r);
        quickSort(nums, l, q-1);
        quickSort(nums, q+1, r);
    }
    // Partition method from Algorithms, CLRS
    int partition1(vector<int> &nums, int l, int r) {
        // Randomly picks an element and swap it with nums[r] as pivot
        int rdm_idx = rand() % (r - l + 1) + l;
        swap(nums[rdm_idx], nums[r]);
        
        int i = l, j = l;
        int val = nums[r];
        for (; j < r; ++j) {
            if (nums[j] < val) {
                swap(nums[i], nums[j]);
                i++;
            }
        }
        swap(nums[i], nums[r]);        
        return i;
    }
    // Partition method from Algorithms, Sedgewick
    int partition2(vector<int> &nums, int l, int r) {
        // Randomly picks an element and swap it with nums[r] as pivot
        int rdm_idx = rand() % (r - l + 1) + l;
        swap(nums[rdm_idx], nums[r]);
        
        int i = l-1, j = r;
        int val = nums[r];
        while (true) {
            while (nums[++i] < val) {}
            while (nums[--j] > val) {
                if (j == l) break;
            }
            if (i >= j) break;
            swap(nums[i], nums[j]);
        }
        swap(nums[i], nums[r]);
        return i;
    }
    void swap(int &a, int &b) {
       int tmp = a;
        a = b;
        b = tmp;
    }
};

// Solution using heap sort with a priority queue built from scratch. Time complexity O(nlgn). Space complexity O(n) from the prioirty queue.
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return nums;
        
        priority_queue<int> pq(nums.begin(), nums.end());
        for (int i = n-1; i >= 0; --i) {
            nums[i] = pq.top();
            pq.pop();
        }
        return nums;
    }
};

class PQ {
public:
    PQ() {
        pq.reserve(50000);
        N = 0;
    }
  
    PQ(const vector<int> &nums) {
        pq = nums;
        N = nums.size();
        for (int k = N / 2 - 1; k >= 0; --k) {
            fixDown(k);
        }
    }
    
    int top() {
        return pq[0];
    }
    
    void pop() {
        swap(pq[0], pq[--N]);
        fixDown(0);
    }
    
private:    
    void fixDown(int i) {
        // has at least a left child
        while (2*i+1 < N) {
            // Find the maximum child
            int j = 2*i+1;
            if (j < N-1 && pq[j+1] > pq[j]) j++;
            // swap if child is larger than parent
            if (pq[i] < pq[j]) {
                swap(pq[i], pq[j]);
                i = j;
            } else break;            
        }
    }
    
    void swap(int &a, int &b) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    std::vector<int> pq;
    int N; // number of elements    
};

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return nums;
        
        PQ pq(nums);
        for (int i = n-1; i >= 0; --i) {
            nums[i] = pq.top();
            pq.pop();
        }
        return nums;
    }
};

// Solution using counting sort because the values lie in a range comparable to n. Time complexity O(n). Space complexity O(n) as it needs 2 additional vectors.
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        vector<int> counts(kMax, 0);
        // Construct counts
        for (const int num : nums) {
            counts[num + kOffset] ++;
        }
        // Accumulate
        for (int i = 1; i < kMax; ++i) {
            counts[i] += counts[i-1];
        }
        // Put integers into the correct location
        vector<int> result(nums.size());
        for (int k = nums.size()-1; k >= 0; --k) {
            int idx = --counts[nums[k] + kOffset];
            result[idx] = nums[k];
        }
        return result;
    }
    
private:
    const int kMax = 100'001;
    const int kOffset = 50'000;
};

// Solution using radix sort with base 10.
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        vector<int> shifted = nums;
        // Shift values so they start at 0.
        for (int i = 0; i < shifted.size(); ++i) {
            shifted[i] += kOffset;
        }
        // radix sort
        for (int base = 1; base <= kMax; base *= 10) {
            shifted = countingSort(shifted, base);
        }
        // Shift back
        for (int i = 0; i < shifted.size(); ++i) {
            shifted[i] -= kOffset;
        }        
        return shifted;
    }
    
    vector<int> countingSort(vector<int>& nums, int base) {
        vector<int> counts(10);        
        // Construct counts
        for (const int num : nums) {
            int digit = (num / base) % 10;
            counts[digit] ++;
        }
        // Accumulate
        for (int i = 1; i < counts.size(); ++i) {
            counts[i] += counts[i-1];
        }
        // Put integers into the correct location
        vector<int> result(nums.size());
        for (int k = nums.size()-1; k >= 0; --k) {
            int digit = (nums[k] / base) % 10;
            int idx = --counts[digit];
            result[idx] = nums[k];
        }
        return result; 
    }
    
private:
    const int kMax = 100'000;
    const int kOffset = 50'000;
};
      
