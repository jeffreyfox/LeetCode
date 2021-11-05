/*
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note: 
You may assume k is always valid, 1 ≤ k ≤ array's length.
*/

// Solution 1. Use a min-queue of k elements. 
// First build the heap from first k elements of array, then insert another and remove the mininum.
// Finally we end up with the k largest numbers of the array. Simple extract the minimum we get the k-th largest element.
// We use the linear O(n) method to build the heap : initialize the heap array and the element count N, and then run fixDown backwards
// Capacity of the heap should be k+2. 1 is for the unused nums[0], the other is for the additional element added before calling deleteMin.

class PQ {
public:
    PQ(int cap) : N(0) {
        nums.resize(cap, 0);
    }
    void buildHeap(const vector<int>& arr, int i, int j) {
        for(int k = i; k <= j; ++k) {
            nums[k-i+1] = arr[k];
        }
        N = j-i+1;
        for(int k = N/2; k > 0; --k)
            fixDown(k);
    }
    void insert(int k) {
        nums[++N] = k;
        fixUp(N);
    }
    int deleteMin() {
        swap(nums[1], nums[N--]);
        fixDown(1);
        return nums[N+1];
    }
    
private:
    void fixUp(int i) {
        while(i > 1 && nums[i/2] > nums[i]) {
            swap(nums[i/2], nums[i]);
            i /= 2;
        }
    }
    void fixDown(int i) {
        while(2*i <= N) {
            int j = 2*i;
            if(j < N && nums[j+1] < nums[j]) j++;
            if(nums[j] < nums[i]) {
                swap(nums[j], nums[i]);
                i = j;
            } else break;
        }
    }
    int N; //number of elements
    vector<int> nums;
};

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        // min-queue of k numbers
        PQ pq(k+2);//maximum capacity k+2
        //build heap from first k numbers
        pq.buildHeap(nums, 0, k-1);
        
        //add one and remove min
        for(int i = k; i < n; i++) {
            pq.insert(nums[i]);
            pq.deleteMin();
        }
        return pq.deleteMin();
    }
};

// Solution 2. Same idea but using STL priority_queue class

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        // min-queue of k numbers
        std::priority_queue<int, std::vector<int>, std::greater<int> > pq;
        //build the heap from first k numbers
        for(int i = 0; i < k; i++) pq.push(nums[i]);
        //add one and remove min
        for(int i = k; i < n; i++) {
            pq.push(nums[i]);
            pq.pop();
        }
        return pq.top();
    }
};

// Solution 3. Use quick selection. Iterative or recursive findKthHelper. Since looking for k-th largest, need to revert implementatino of traditional partition function.
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        return findKthHelper(nums, 0, n-1, k);
    }
    int findKthHelper(vector<int>& nums, int l, int r, int k) {
        while(l < r) {
            //if(l == r) return nums[l];
            int i = partition(nums, l, r);
            int cnt = i-l+1; //number of elements between [l, i]
            if(k == cnt) return nums[i];
            else if(k < cnt) r = i-1; 
            else { l = i+1; k -= cnt; }
        }
        return nums[l];
    }
    /* 
    //recursive findKthHelper
    int findKthHelper(vector<int>& nums, int l, int r, int k) {
        if(l == r) return nums[l];
        int i = partition(nums, l, r);
        int cnt = i-l+1; //number of elements between [l, i]
        if(k == cnt) return nums[i];
        else if(k < cnt) return findKthHelper(nums, l, i-1, k);
        else return findKthHelper(nums, i+1, r, k-cnt);
    }
    */
    //no need to check l, r bounds because calling function guards against it. 
    //opposite to traditional paritition (larger ones to the left, smaller ones to the right)
    int partition(vector<int>& nums, int l, int r) {
        int x = nums[r]; //pivot is last one
        int i = l-1, j = r;
        while(1) {
            while(nums[++i] > x) ;
            while(nums[--j] < x) if(j == l) break;
            if(i < j) swap(nums[i], nums[j]);
            else break;
        }
        swap(nums[i], nums[r]);
        return i;
    }
};

// 2021.11
// First build a heap structure from nums[0] to nums[N-1]. N-1 is the last non-leaf node.
// Then pop the max k times
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // First build a heap structure. N/2 -1 is the last non-leaf node
        int n = nums.size();
        for (int i = n/2-1; i >= 0; i--) {
            fixDown(nums, i, n);
        }            
        // Then pop the max k-1 times
        for (int i = 1; i < k; ++i) {
            swap(nums, 0, n-1);
            n = n-1;
            // Fix the root
            fixDown(nums, 0, n);
        }
        // The at the k-th time, the root is the one we need.
        return nums[0];
    }
    
private:    
    // i is the index to fix, n is the number of elements in the heap (num[0] .. num[n-1])
    void fixDown(vector<int>& nums, int i, int n) {
        while (2*i+1 < n) {
            // j is the largest child
            int j = 2*i+1;          
            if (j < n-1 && nums[j] < nums[j+1]) j++;
            if (nums[i] >= nums[j]) break;
            swap(nums, i, j);
            i = j;
        }
    }
    void swap(vector<int>& nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};
