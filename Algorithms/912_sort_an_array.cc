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
      
