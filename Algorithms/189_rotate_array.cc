/*
Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.

[show hint]
Hint:
Could you do it in-place with O(1) extra space?

Related problem: Reverse Words in a String II
*/

// Solution 1. Three reverse passes.

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k = k % n;
        if(k == 0) return;
        reverse(nums, 0, n);
        reverse(nums, 0, k);
        reverse(nums, k, n);
    }
    //reverse nums[beg, end). excluding end.
    void reverse(vector<int>& nums, int beg, int end) {
        int i = beg, j = end-1;
        while(i < j)  swap(nums[i++], nums[j--]);
    }
};

// Solution 2. Juggling method (do-while loop). Need to get gcd of two numbers

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k = k % n;
        if(k == 0) return;
        int tmp = 0;
        for(int i = 0; i < gcd(k, n); ++i) {
            int j = i;
            tmp = nums[j];
            do {
                //copy nums[i] to nums[j]
                j = (j+k) % n;
                swap(tmp, nums[j]);
            } while(j != i);
        }
    }
    int gcd(int a, int b) {
        if(a == 0) return b;
        if(b == 0) return a;
        if(a > b) return gcd(b, a);
        return gcd(b-a, a);
    }
};

// Solution 3. Improved version of solution 2. Use shift insteaad of swapping, only swap once (similar idea to insertion sort).
// Also a simpler gcd algorithm (Euclid).
// If b == 0, return a,
// If b != 0, then return gcd(b, a%b). Two cases:
// if (b > a), then it goes to gcd(b, a), effectively swapping the two
// if (b == a), then it goes to gcd(b, 0), and it immediately returns b
// if (b < a), then it goes to gcd(b, a%b), and we effectively reduces the first argument from a to b.
// So the algorithm always decreases the first argument for each gcd run.

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k = k % n;
        if(k == 0) return;
        for(int i = 0; i < gcd(k, n); ++i) {
            int j = i;
            int tmp = nums[j];
            while(1) {
                //copy nums[i] to nums[j]
                int l = (j-k+n) % n;
                if(l == i) break;
                nums[j] = nums[l];
                j = l;
            } 
            nums[j] = tmp;
        }
    }
    int gcd(int a, int b) {
        if(b == 0) return a;
        return gcd(b, a%b);
    }
/*  //iterative gcd, same idea as recursive one
    int gcd(int a, int b) {
        while(b) {
            int tmp = b;
            b = a % b;
            a = tmp;
        }
        return a;
    }        
*/
};

// Solution 4. Use a temp vector. O(n) space.

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k = k % n;
        if(k == 0) return;
        vector<int> tmp(n, 0);
        for(int i = 0; i < n; ++i) 
            tmp[(i+k)%n] = nums[i];
        nums = tmp;
    }
};

// Solution 5. Shift one by one, will cause TLE. O(nk) time.
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k = k % n;
        if(k == 0) return;
        for (int i = 0; i < k; ++i) {
            rotateByOne(nums);
        }
    }
    //reverse nums[beg, end)
    void rotateByOne(vector<int>& nums) {
        int reg = nums.back();
        for (int i = 0; i < nums.size(); ++i) {
            int tmp = nums[i];
            nums[i] = reg;
            reg = tmp;
        }
    }
};

