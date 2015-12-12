/*
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Note:

    You must not modify the array (assume the array is read only).
    You must use only constant, O(1) extra space.
    Your runtime complexity should be less than O(n2).
    There is only one duplicate number in the array, but it could be repeated more than once.
*/

/*
Recursive solution.  O(nlgn) time.
Use a helper function to find duplicates in nums array in interval [lo, hi], given that the num array has more than hi-lo+1 elements lying in [lo, hi] (pigeon hole principle).
For given lo and hi, we let mid = (lo+hi)/2. We count the # elements <= mid (denoted as smaller), and # elements > mid (denoted as larger). Two cases:
1. [lo, hi] contains even number of integers. If no duplicates, we should find # integers <= mid equal to # integers > mid.
e.g. [2, 7], mid = 4, thus smaller = #[2,3,4] = 3, larger = #[5,6,7] = 3.
If duplicate <= mid, thus we have smaller > larger, otherwise smaller < larger
2. [lo, hi] contains odd number of integers. If no duplicates, we should find # integers <= mid one more than # integers > mid.
e.g. [2, 8], mid = 5, thus smaller = #[2,3,4,5] = 4, larger = #[6,7,8] = 3.
If duplicate <= mid, thus we have smaller > larger, otherwise smaller <= larger
Thus we have come up with the recursive formula:
 - smaller > larger => check again for interval [lo, mid]
 - smaller < larger => check again for interval [mid+1, hi].
Repeat until lo == hi, where we know that duplicate is of course lo (the only possible choice between [lo, hi]).
*/

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        return findDuplicateHelper(nums, 1, n-1);
    }
    int findDuplicateHelper(vector<int>& nums, int lo, int hi) {
        if(lo > hi) return -1;
        if(lo == hi) return lo;
        int n = nums.size();
        int mid = lo + (hi-lo)/2;
        int small = 0, large = 0;
        for(int i = 0; i < n; ++i) {
            if(nums[i] < lo || nums[i] > hi) continue; //ignore elements out of range [lo, hi]
            if(nums[i] <= mid) small++;
            else large++;
        }
        if(small > large) return findDuplicateHelper(nums, lo, mid);
        else return findDuplicateHelper(nums, mid+1, hi);
    }
};

// Solution 2. Same ideas as 1. Iterative solution.  O(nlgn) time.

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        int lo = 1, hi = n-1;
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            int small = 0, large = 0;
            for(auto it : nums) {
                if(it < lo || it > hi) continue; //ignore elements out of range [lo, hi]
                if(it <= mid) small++;
                else large++;                
            }
            if(small > large) hi = mid;
            else lo = mid+1;
        }
        return lo;
    }
};

/*
Solution 3. Another binary search solution. O(nlgn) time.
For each number i in [1 .. n-1], count number of elements smaller or equal than i, denoted as p[i]. What will we get?
If no duplicate, e.g. [1,2,3,4]. then p[i] = i, for i = 1,.. 4. But if there is a duplicate, e.g. [1,2,2,3,4], we have 
p[1] = 1, p[2] = 3, p[3] = 4, p[4] = 5. p[i] becomes larger than i starting from the duplicated number. Since we only have one unique duplicated number, this observation always holds. Thus we can use binary search to determine i. 
Initially lo = 1, hi = n-1, and mid = (lo+hi)/2. Scan whole array and count number of elements <= mid. if count > mid, then we know that duplicate lies in [lo, mid], so we make hi = mid. Otherwise, we know that we haven't encountered the duplicate yet, and duplicate lies in [mid+1, hi], so we make lo = mid+1. Break when lo == hi, and we return lo.
*/

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        int lo = 1, hi = n-1;
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            int count = 0;
            for(int i = 0; i < n; ++i) {
                if(nums[i] <= mid) count++;
            }
            if(count > mid) hi = mid;
            else lo = mid+1;
        }
        return lo;
    }
};

// Solution 4. Smart solution using cycle detection algorithm in linked-lists
// See http://keithschwarz.com/interesting/code/?dir=find-duplicate

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        int fast = n-1, slow = n-1;
        do {
            fast = nums[fast]-1;
            fast = nums[fast]-1;
            slow = nums[slow]-1;
        } while(fast != slow);
        slow = n-1;
        while(fast != slow) {
            fast = nums[fast]-1;
            slow = nums[slow]-1;
        }
        return slow+1;
    }
};


