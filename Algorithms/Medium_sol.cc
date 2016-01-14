/**************************************************** 
 ***    307,Medium,Range Sum Query - Mutable 
 ****************************************************/

/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
The update(i, val) function modifies nums by updating the element at index i to val.

Example:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8

Note:

    The array is only modifiable by the update function.
    You may assume the number of calls to update and sumRange function is distributed evenly.
*/

// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.update(1, 10);
// numArray.sumRange(1, 2);

// Solution using binary indexed tree, find and update both O(logn).
// A little tricky in update function. Need to calculate the difference between current value and old value.
// Also uses 1-based indexing, so need to take care of the offset.

class NumArray {
public:
    NumArray(vector<int> &nums) {
        n = nums.size(); //0 is dummy node
        bitsum.resize(n+1, 0);
        num.resize(n+1, 0);
        for(int i = 0; i < n; ++i) {
           update(i, nums[i]); //i is index in nums
        }
    }

    int sumRange(int i, int j) {
        if(i > j || i < 0 || j >= n) return 0;
        if(i == j) return num[i+1];
        return getSum(j) - getSum(i-1);
    }

    void update(int i, int val) {
        int error = val - num[++i];
        num[i] = val;
        while(i <= n) {
            bitsum[i] += error;
            i += (i & (-i)); 
        }
    }
private:
    //accumulated sum from nums[0 .. i]
    int getSum(int i) {
        if(i < 0 || i >= n) return 0;
        i++;
        int sum = 0;
        while(i > 0) {
            sum += bitsum[i];
            i -= (i & (-i));
        }
        return sum;
    }
    vector<int> num;
    vector<int> bitsum;
    int n;
};


/**************************************************** 
 ***    304,Medium,Range Sum Query 2D - Immutable 
 ****************************************************/

/*
Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:

Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12

Note:

    You may assume that the matrix does not change.
    There are many calls to sumRegion function.
    You may assume that row1 ≤ row2 and col1 ≤ col2.
*/

// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.sumRegion(1, 2, 3, 4);

// DP solution similar to the 1D problem (303).

class NumMatrix {
public:
    NumMatrix(vector<vector<int>> &matrix) {
        if(matrix.empty() || matrix[0].empty()) {
            m = n = 0;
            return;
        }
        m = matrix.size(); n = matrix[0].size();
        sum.resize(m+1, vector<int>(n+1, 0));
        for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= n; ++j)
                sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + matrix[i-1][j-1];
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        if(row1 < 0 || row1 >= m || col1 < 0 || col1 >= n) return 0;
        if(row2 < 0 || row2 >= m || col2 < 0 || col2 >= n) return 0;
        return sum[row2+1][col2+1] - sum[row1][col2+1] - sum[row2+1][col1] + sum[row1][col1];
    }
    vector<vector<int> > sum;
    int m, n;
};


/**************************************************** 
 ***    285,Medium,Inorder Successor in BST 
 ****************************************************/

/*
Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
Several cases:
1. If p has right subtree, then just return the minimum in right subtree.
2. Otherwise, need to go to its ancestors. First build a search path from root to p, then search backwards, if found a path going toward left, then the higher one is the successor.
3. If not found such path, that means p is lying at bottom right of tree, and there is no successor. Return NULL.
Caveats:
tree is BST! So don't use backtracking to seach for path, use O(logn) iterative approach utilizing BST properly!

*/

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root || !p) return NULL;
        if(p->right) return findMin(p->right);
        //need to find path from root to p
        vector<TreeNode*> path;
        bool found = findPath(root, p, path);
        if(!found) return NULL;
        int n = path.size(), i = 0;
        for(i = n-1; i > 0; i--) {
            //is left subtree
            if(path[i-1]->left == path[i]) return path[i-1];
        }
        return NULL;
    }
    bool findPath(TreeNode* root, TreeNode* p, vector<TreeNode*>& path) {
        while(root) {
            path.push_back(root);
            if(root == p) return true;
            else if(p->val < root->val) root = root->left;
            else root = root->right;
        }
        return false;
    }
    TreeNode* findMin(TreeNode* root) {
        while(root->left) root = root->left;
        return root;
    }
};

//Alternative solution using a stack
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root || !p) return NULL;
        if(p->right) return findMin(p->right);
        //need to find path from root to p
        stack<TreeNode*> path;
        bool found = findPath(root, p, path);
        if(!found) return NULL;
        while(!path.empty()) {
            TreeNode *ancestor = path.top(); 
            path.pop(); 
            //is left subtree
            if(!path.empty() && path.top()->left == ancestor) return path.top();
        }
        return NULL;
    }
    bool findPath(TreeNode* root, TreeNode* p, stack<TreeNode*>& path) {
        while(root) {
            path.push(root);
            if(root == p) return true;
            else if(p->val < root->val) root = root->left;
            else root = root->right;
        }
        return false;
    }
    TreeNode* findMin(TreeNode* root) {
        while(root->left) root = root->left;
        return root;
    }
};



/**************************************************** 
 ***    284,Medium,Peeking Iterator 
 ****************************************************/

/*
Given an Iterator class interface with methods: next() and hasNext(), design and implement a PeekingIterator that support the peek() operation -- it essentially peek() at the element that will be returned by the next call to next().

Here is an example. Assume that the iterator is initialized to the beginning of the list: [1, 2, 3].

Call next() gets you 1, the first element in the list.

Now you call peek() and it returns 2, the next element. Calling next() after that still return 2.

You call next() the final time and it returns 3, the last element. Calling hasNext() after that should return false.

Hint:

    Think of "looking ahead". You want to cache the next element.
    Is one variable sufficient? Why or why not?
    Test your design with call order of peek() before next() vs next() before peek().
    For a clean implementation, check out Google's guava library source code. 

Follow up: How would you extend your design to be generic and work with all types, not just integer?
*/

// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};

// Store a cache in peekingIterator. Remember to set and unset the boolean tag.

class PeekingIterator : public Iterator {
public:
        PeekingIterator(const vector<int>& nums) : Iterator(nums) {
            // Initialize any member here.
            // **DO NOT** save a copy of nums and manipulate it directly.
            // You should only use the Iterator interface methods.
            hasPeek = false; 
            peekVal = -1;
        }

    // Returns the next element in the iteration without advancing the iterator.
        int peek() {
            if(!hasPeek) {
                peekVal = Iterator::next();
                hasPeek = true;
            }
            return peekVal;
        }

        // hasNext() and next() should behave the same as in the Iterator interface.
        // Override them if needed.
        int next() {
            if(hasPeek) {
                hasPeek = false;
                return peekVal;
            } else return Iterator::next();
        }

        bool hasNext() const {
            return hasPeek || Iterator::hasNext();
        }
private:
    bool hasPeek;
    int peekVal;
};


/**************************************************** 
 ***    281,Medium,Zigzag Iterator 
 ****************************************************/

/*
Given two 1d vectors, implement an iterator to return their elements alternately.

For example, given two 1d vectors:

v1 = [1, 2]
v2 = [3, 4, 5, 6]

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].

Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

Clarification for the follow up question - Update (2015-09-18):
The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases. If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For example, given the following input:

[1,2,3]
[4,5,6,7]
[8,9]

It should return [1,4,8,2,5,9,3,6,7]. 
*/

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */

// pointer always points to the the next valid value. After robtaining the next value, move pointer to next valid value.

class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        nums.push_back(v1); 
        nums.push_back(v2);
        n = 2;
        indices.resize(n, 0);        
        arrayIdx = 0;
        while(arrayIdx < n && nums[arrayIdx].empty()) arrayIdx++;
    }

    int next() {
        if(arrayIdx == n) return -1;

        int idx = indices[arrayIdx];
        int val = nums[arrayIdx][idx];

        indices[arrayIdx]++;
        int i = (arrayIdx+1) % n;
        while(i != arrayIdx && indices[i] == nums[i].size()) i = (i+1) % n;
        if(i == arrayIdx && indices[i] == nums[i].size()) arrayIdx = n;
        else arrayIdx = i;

        return val;
    }

    bool hasNext() {
        return arrayIdx < n;
    }
private:
    vector<vector<int> > nums;
    vector<int> indices; //current position in each array
    int arrayIdx; //current array index
    int n; //number of arrays
};


/**************************************************** 
 ***    280,Medium,Wiggle Sort 
 ****************************************************/

/*
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4]. 
*/

// Linear solution:
/* Scan left to right, two passes
 First pass arranges i and i+1 for even i such that nums[i] >= nums[i+1].
 Second pass arranges i and i+1 for odd i such that nums[i] <= nums[i+1].
 In second pass, we could have (i is odd), then we simply swap i and i+1.
               *                   *
           *                 * \  /
        *           =>      /   *
   *                       *
   (i-1 i) (i+1 
*/

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return;
        for(int i = 0; i+1 < n; i+=2) {
            if(nums[i] > nums[i+1]) swap(nums, i, i+1);
        }
        for(int i = 1; i+1 < n; i+=2) {
            if(nums[i] < nums[i+1]) swap(nums, i, i+1);
        }
    }
    void swap(vector<int>& nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
};

// One pass linear solution. We can combine the two passes into one pass.
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return;
        for(int i = 0; i+1 < n; i++) {
            if(!(i & 1) && nums[i] > nums[i+1]) swap(nums, i, i+1);
            if((i & 1) && nums[i] < nums[i+1]) swap(nums, i, i+1);
        }
    }
    void swap(vector<int>& nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
};

// Another O(nlgn) solution using sort. First sort, then swap ajacent pairs.
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return;
        sort(nums.begin(), nums.end());
        for(int i = 1; i+1 < n; i+=2) {
            int tmp = nums[i];
            nums[i] = nums[i+1];
            nums[i+1] = tmp;
        }
    }
};

/**************************************************** 
 ***    268,Medium,Missing Number 
 ****************************************************/

/*
 Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

For example,
Given nums = [0, 1, 3] return 2.

Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity? 
*/

// solution by swapping. Since numbers are distinct, don't need to worry about infinite while loops due to duplicate entries.

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            while(nums[i] != i && nums[i] != n) {
                swap(nums[i], nums[nums[i]]);
            }
        }
        for(int i = 0; i < n; ++i)
            if(nums[i] != i) return i;
        return n;
    }
};


/**************************************************** 
 ***    267,Medium,Palindrome Permutation II 
 ****************************************************/

/*
Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.

For example:

Given s = "aabb", return ["abba", "baab"].

Given s = "abc", return [].

Hint:

    If a palindromic permutation exists, we just need to generate the first half of the string.
    To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.

*/

// Scan whole word, count occurrences of each character. Only one character is allowed to have odd count. Otherwise return empty set.
// construct half string as half the count of each character. No need to sort the string because we construct it from c = 0 to c = 255.
// Store the middle character as a string (either single character, or empty string). And call nextPermutation to find the next one. Need a reverse function.
// Caveats:
// Need to handle corner cases where the half string is empty! It will result in infinite loops in nextPermutation if there is no checking.
// Alternatively can check this at the beginning (by checking whether the length of s is 1).

class Solution {
public:
    vector<string> generatePalindromes(string s) {
        vector<string> result;
        if(s.empty()) return result;
        if(s.size() == 1) {
            result.push_back(s); return result;
        }
        vector<int> counts(256, 0);
        for(auto c : s) counts[c] ++;
        int nodds = 0;
        string odd = "";
        s = "";
        for(int c = 0; c < 256; ++c) {
            if(counts[c] & 1) {
                odd += c;
                if(++nodds > 1) return result; //no solution
            } 
            if (counts[c] > 0)
                s += string(counts[c]/2, c);
        }
        result.push_back(s+odd+reverse(s));
        while(nextPermutation(s)) result.push_back(s+odd+reverse(s));
        return result;
    }
    
    string reverse(const string& s) {
        string t = s;
        int i(0), j(s.size()-1);
        while(i < j) {
            swap(t[i++], t[j--]);
        }
        return t;
    }
    bool nextPermutation(string& s) {
        if(s.empty()) return false;
        int n = s.size();
        int k = n-2, l = n-1;
        while(k >= 0 && s[k] >= s[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) { //no next, just return false
            return false;
        }
        while(l > k && s[l] <= s[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(s[k], s[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(s[i++], s[j--]);
        return true;
    }
};

/**************************************************** 
 ***    264,Medium,Ugly Number II 
 ****************************************************/

/*
Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number.

Hint:

    The naive approach is to call isUgly for every number until you reach the nth one. Most numbers are not ugly. Try to focus your effort on generating only the ugly ones.
    An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly number.
    The key is how to maintain the order of the ugly numbers. Try a similar approach of merging from three sorted lists: L1, L2, and L3.
    Assume you have Uk, the kth ugly number. Then Uk+1 must be Min(L1 * 2, L2 * 3, L3 * 5).
*/

// Solution: http://www.geeksforgeeks.org/ugly-numbers/
// All ugly numbers are built from the following three lists:
// (1) 1x2 2x2 3x2 4x2 5x2 6x2 8x2
// (2) 1x3 2x3 3x3 4x3 5x3 6x3 8x3
// (3) 1x5 2x5 3x5 4x5 5x5 6x5 8x5
// Where (1) is built from the exact ugly number sequence multiple by 2, and similar for (2) and (3). So we could use dynamic programming to generate the next ugly number from previous ones. The key is to maintain the order.
// To solve this, we keep track of which is the last ugly number used in each list, for example, 4 in (1), 3 in (2), and 2 in (5), then the next ugly number will be the minimum of 4x2, 3x3, and 2x5. We found the minimum is 4x2 from (1), then we advance pointer in (1) to 5. We store all the previous ugly numbers in an array so that we can use three pointers to point to the approapriate entry in the array and easily find the next ugly number for each list by advancing the pointers. 
// There might be duplicates in the lists, so we need to test each list.

// A simple solution with many array addressing (a bit slower)
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 1) return 1;
        int mult2 = 1, mult3 = 1, mult5 = 1;
        vector<int> ugly(n, 1);
        int i2 = 0, i3 = 0, i5 = 0; //index in ugly array
        for(int i = 1; i < n; ++i) {
            ugly[i] = min(min(ugly[i2]*2, ugly[i3]*3), ugly[i5]*5);
            if(ugly[i] == ugly[i2]*2) i2++;
            if(ugly[i] == ugly[i3]*3) i3++;
            if(ugly[i] == ugly[i5]*5) i5++;
        }
        return ugly[n-1];
    }
};

// A faster version avoiding array addressing by using intermediate variable mult and next
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 1) return 1;
        int mult2 = 1, mult3 = 1, mult5 = 1;
        vector<int> ugly(n, 1);
        int i2 = 0, i3 = 0, i5 = 0; //index in ugly array
        for(int i = 1; i < n; ++i) {
            int next = min(min(mult2*2, mult3*3), mult5*5);
            ugly[i] = next;
            if(next == mult2*2) mult2 = ugly[++i2];
            if(next == mult3*3) mult3 = ugly[++i3];
            if(next == mult5*5) mult5 = ugly[++i5];
        }
        return ugly[n-1];
    }
};

/**************************************************** 
 ***    260,Medium,Single Number III 
 ****************************************************/

/*
Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:

    The order of the result is not important. So in the above example, [5, 3] is also correct.
    Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
*/

// Solution using bit operations. Since the two numbers are different, they should differ by at least one bit position. Say the position is i, then one number should have 0, the other have 1 at this position. We use exlcusive or to find the bits that they differ. Then extract one bit out. And then group the numbers by whether the bit is set or not. We effectively break the problem into two easier problems where each group has only one single number. We calculate the single number for each group separately.

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> result(2, 0);
        int val = 0, n = nums.size();
        for(int i = 0; i < n; ++i) {
            val ^= nums[i];
        }
        //val should be non-zero. Extract one none zero digit.
        val = val & (val ^ (val-1)); //now val has only one digit set
        for(int i = 0; i < n; ++i) {
            if(nums[i] & val) result[0] ^= nums[i];
            else result[1] ^= nums[i];
        }
        return result;
    }
};




/**************************************************** 
 ***    259,Medium,3Sum Smaller 
 ****************************************************/

/*
Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

For example, given nums = [-2, 0, 1, 3], and target = 2.

Return 2. Because there are two triplets which sums are less than 2:

[-2, 0, 1]
[-2, 0, 3]

Follow up:
Could you solve it in O(n2) runtime? 
*/

// Two pointers, similar to 3sum.
// Optimization: break if sum is too large.

class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int count = 0;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 0; i < n-2; i++) {
            int res = target - nums[i];
            if(nums[i+1] + nums[i+2] >= res) break;
            int j = i+1, k = n-1;
            while(j < k) {
               if(nums[j] + nums[k] < res) { count += k-j; j++; }
               else k--;
            }
        }
        return count;
    }
};

/**************************************************** 
 ***    256,Medium,Paint House 
 ****************************************************/

/*
There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.
*/

// Solution: Dynamic programming
// Keep the cost for painting the first k houses with last house colored as R/G/B.
// The k+1 house can choose among R/G/B, with cost as
// cost_so_far[R]:  cost[k+1][R] + min(cost_so_far[G], cost_so_far[B])
// and similar for other two cases.

class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if(costs.empty() || costs[0].empty()) return 0;
        int n = costs.size();
        vector<int> cost_so_far(3, 0);
        for(int i = 0; i < n; ++i) {
            int t0 = min(cost_so_far[1], cost_so_far[2]) + costs[i][0];
            int t1 = min(cost_so_far[0], cost_so_far[2]) + costs[i][1];
            int t2 = min(cost_so_far[0], cost_so_far[1]) + costs[i][2];
            cost_so_far[0] = t0;
            cost_so_far[1] = t1;
            cost_so_far[2] = t2;
        }
        return min(min(cost_so_far[0], cost_so_far[1]), cost_so_far[2]);
    }
};

/**************************************************** 
 ***    254,Medium,Factor Combinations 
 ****************************************************/

/*
Numbers can be regarded as product of its factors. For example,

8 = 2 x 2 x 2;
  = 2 x 4.

Write a function that takes an integer n and return all possible combinations of its factors.

Note:

    Each combination's factors must be sorted ascending, for example: The factors of 2 and 6 is [2, 6], not [6, 2].
    You may assume that n is always positive.
    Factors should be greater than 1 and less than n.

Examples:
input: 1
output:

[]

input: 37
output:

[]

input: 12
output:

[
  [2, 6],
  [2, 2, 3],
  [3, 4]
]

input: 32
output:

[
  [2, 16],
  [2, 2, 8],
  [2, 2, 2, 4],
  [2, 2, 2, 2, 2],
  [2, 4, 4],
  [4, 8]
]
*/

// Recursive DFS solution. Avoid adding [n] to solution (checking tmp.empty()).
// Also avoid pushing duplicated entries, e.g. [2, 2, 3], [2, 3, 2]. This is done by the j*j <= n condition in the loop.
class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int> > result;
        if(n <= 2) return result; //empty
        vector<int> tmp;
        dfs(n, 2, tmp, result); // start searching factors from 2 to sqrt(n)
        return result;
    }
    void dfs(int n, int i, vector<int>& tmp, vector<vector<int> >& result) {
        tmp.push_back(0);
        if(!tmp.empty()) { //push n itself
            tmp.back() = n;
            result.push_back(tmp);
        }
        //now check factors
        for(int j = i; j*j <= n; ++j) {
            if(n % j != 0) continue; //not a factor
            tmp.back() = j;
            dfs(n/j, j, tmp, result); //now start searching from j
        }
        tmp.pop_back();
    }
};


/**************************************************** 
 ***    253,Medium,Meeting Rooms II 
 ****************************************************/

/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2. 
*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

//Solution 1: sort the ending point according to its coordinate and type (start/end). If ties on coordinate, end goes before start
//Then do sweeping line and count. When see a start point, increment count, otherwise decrement count.

struct EndPoint {
    int val;
    int type; //0 for starting, 1 for ending
    EndPoint(): val(0), type(0) {}
    EndPoint(int v, int t) : val(v), type(t) {}
};

bool compare(const EndPoint& a, const EndPoint& b) {
    if(a.val == b.val) return a.type < b.type;
    else return a.val < b.val;
}


class Solution {
public:

    int minMeetingRooms(vector<Interval>& intervals) {
        int n = intervals.size();
        if(n <= 1) return n;
        vector<EndPoint> points(2*n);
        for(int i = 0; i < n; ++i) {
            points[2*i] = EndPoint(intervals[i].start, 2);
            points[2*i+1] = EndPoint(intervals[i].end, 1);
        }
        sort(points.begin(), points.end(), compare);
        int count = 0, result = 0;
        for(int i = 0; i < 2*n; ++i) {
            if(points[i].type == 2) { //is start point
               count++;
               result = max(result, count);
            } else count--;
        }
        return result;
    }
};


//A simpler solution: use a map to keep order, and count individual points, then iterate orderly through map
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> dict;
        int n = intervals.size();
        if(n <= 1) return n;
        for(int i = 0; i < n; ++i) {
            dict[intervals[i].start]++;
            dict[intervals[i].end]--;
        }
        int count = 0, max_count = 0;
        for(auto it : dict) { //ordered iterator
            count += it.second;
            max_count = max(count, max_count);
        }
        return max_count;
    }
};


/**************************************************** 
 ***    251,Medium,Flatten 2D Vector 
 ****************************************************/

/*
Implement an iterator to flatten a 2d vector.

For example,
Given 2d vector =

[
  [1,2],
  [3],
  [4,5,6]
]

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].

Hint:

    How many variables do you need to keep track?
    Two variables is all you need. Try with x and y.
    Beware of empty rows. It could be the first few rows.
    To write correct code, think about the invariant to maintain. What is it?
    The invariant is x and y must always point to a valid point in the 2d vector. Should you maintain your invariant ahead of time or right when you need it?
    Not sure? Think about how you would implement hasNext(). Which is more complex?
    Common logic in two different places should be refactored into a common method.

Follow up:
As an added challenge, try to code it using only iterators in C++ or iterators in Java. 
*/

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */

class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        nums = vec2d;
        n = nums.size();
        index = 0;
        arrayIdx = 0;
        while(arrayIdx < n && nums[arrayIdx].empty()) arrayIdx++;
    }

    int next() {
        if(arrayIdx == n) return -1;
        int val = nums[arrayIdx][index];
        index++;
        if(index == nums[arrayIdx].size()) {
            index = 0;
            arrayIdx ++;
            while(arrayIdx < n && nums[arrayIdx].empty()) arrayIdx ++;
        }
        return val;
    }

    bool hasNext() {
        return arrayIdx < n;
    }

private:
    vector<vector<int> > nums;
    int arrayIdx; //current array index
    int index; //index within current array
    int n; //number of arrays
};


/**************************************************** 
 ***    247,Medium,Strobogrammatic Number II 
 ****************************************************/

/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Find all strobogrammatic numbers that are of length = n.

For example,
Given n = 2, return ["11","69","88","96"]. 
*/

// Solution 1. Recursive. First add solutions with leading zeros and put them in the end of vector. then erase them altogether.

class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        vector<string> result;
        if(n == 1) {
            result = {"0", "1", "8"};
            return result;
        }
        stroboHelper(n, result);
        //remove ones starting with zero
        int i = 0;
        for(i = 0; i < result.size(); ++i) {
            if(result[i][0] == '0') break;
        }
        result.resize(i);
        return result;
    }
    void stroboHelper(int n, vector<string>& result) {
        if(n == 1) result = {"1", "8", "0"}; 
        else if(n == 2) result = {"11", "69", "88", "96", "00"};
        else {
            vector<string> tmp;
            stroboHelper(n-2, tmp);
            for(auto it : tmp) {
                result.push_back('1'+it+'1');
                result.push_back('6'+it+'9');
                result.push_back('8'+it+'8');
                result.push_back('9'+it+'6');
            }
            for(auto it : tmp) result.push_back('0'+it+'0');
        }
    }
};

// Solution 2. Iterative. Avoid the annoying leading 0 issue by checking whether reaching last step.

class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        if(n <= 0) return vector<string>();
        if(n == 1) return {"0", "1", "8"};
        if(n == 2) return {"11", "69", "88", "96"};
        vector<string> result;
        if(n % 2 == 1) result = {"0", "1", "8"};
        else result = {"00", "11", "69", "88", "96"};
        vector<string> newresult;
        while(n > 2) {
            n -= 2;
            for(auto it : result) {
                if(n > 2) newresult.push_back('0'+it+'0');
                newresult.push_back('1'+it+'1');
                newresult.push_back('6'+it+'9');
                newresult.push_back('8'+it+'8');
                newresult.push_back('9'+it+'6');
            }
                
            result.swap(newresult);
            newresult.clear();
        }

        return result;
    }
};


/**************************************************** 
 ***    241,Medium,Different Ways to Add Parentheses 
 ****************************************************/

/*
Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.

Example 1

Input: "2-1-1".

((2-1)-1) = 0
(2-(1-1)) = 2

Output: [0, 2]

Example 2

Input: "2*3-4*5"

(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10

Output: [-34, -14, -10, -10, 10]
*/

// Dynamic programming solution.
// First parse string and save numbers and operators separately.
// Then start from bottom up, for large string break into small pieces and check all options.

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        if(input.empty()) return vector<int>();
        vector<int> nums; 
        vector<char> ops;
        parse(input, nums, ops);
        int n = nums.size(); //number of numbers
        //mp[i][j]: outcomes from i (i = [0..n]) numbers starting at j (j = [0 .. n-1]). 
        vector<vector<vector<int> > > mp(n+1, vector<vector<int> >(n, vector<int>()));
        //len = 1 case
        for(int i = 0; i < n; ++i) {
           mp[1][i].push_back(nums[i]);
        }
        for(int len = 2; len <= n; ++len) {
            for (int i = 0; i + len <= n; ++i) {
                int j = i + len - 1; //i start, j end, inclusive
                //try to break it from i+1 .. to j-1
                for(int k = i; k < j; ++k) { // break like this: num[k] | op[k] | num[k+1]
                    for(auto it1 : mp[k-i+1][i]) {
                        for(auto it2 : mp[j-k][k+1]) {
                            mp[len][i].push_back(eval(it1, it2, ops[k]));
                        }
                    }
                }
            }
        }
        return mp[n][0];
    }
    
    int eval(int v1, int v2, char op) {
       if(op == '+') return v1+v2;
       if(op == '-') return v1-v2;
       if(op == '*') return v1*v2;
       return 0;
    }

    void parse(string& input, vector<int>& nums, vector<char>& ops) {
        int val = 0;
        for(int i = 0; i < input.size(); ++i) {
            char c = input[i];
            if(isdigit(c)) {
               val = 10*val + (c - '0');
            } else {
               ops.push_back(c);
               nums.push_back(val);
               val = 0;
            }
        }
        nums.push_back(val); //don't forget last one!
    }
};

// Recursive solution using divide and conquer. Final vector is the cartesian product of two sub-vectors

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> numbers;
        vector<char> operators;
        int num = 0;
        for(int i = 0; i < input.size(); i++) {
            char c = input[i];
            if(c >= '0' && c <= '9') num = num*10 + (c-'0');
            else {
                numbers.push_back(num);
                operators.push_back(c);
                num = 0;
            }
        }
        numbers.push_back(num);
        
        int n = numbers.size();
        vector<int> ret;
        eval(numbers, operators, 0, n-1, ret);
        return ret;
    }
    
    void eval(vector<int>& numbers, vector<char>& operators, int lo, int hi, vector<int>& vals) {
        vals.clear();
        if(lo == hi) {
            vals.push_back(numbers[lo]); //only one
            return;
        }
        vector<int> v1, v2;
        for(int mid = lo; mid < hi; ++mid) {
            eval(numbers, operators, lo, mid, v1);
            eval(numbers, operators, mid+1, hi, v2);
            for (int j1 = 0; j1 < v1.size(); ++j1) {
                for(int j2 = 0; j2 < v2.size(); ++j2) {
                    vals.push_back(eval(v1[j1], v2[j2], operators[mid]));
                }
            }
        }
    }
    
    int eval(int n1, int n2, char op) {
        switch (op) {
            case '+': return n1 + n2;
            case '-': return n1 - n2;
            case '*': return n1 * n2;
            default : return 0;
        }
    }
};

/**************************************************** 
 ***    238,Medium,Product of Array Except Self 
 ****************************************************/

/*
Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)
*/

/// O(n) time, O(1) space solution.
/// Two passes, one from left and one from right
/// Product without self = product of all elements to the left, times product of all elements to the right
/// First pass, calculate products of all elements to the left and save it to ret array
/// Second pass, calculate products of all elements to the right, and multiple to the ret array values
/// when done, return the ret array

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, 1);
        int t = 1;
        for (int i = 1; i < n; ++i)
            ret[i] = ret[i-1]*nums[i-1];
        for (int i = n-2; i >= 0; --i) {
            t *= nums[i+1];
            ret[i] *= t;
        }
        return ret;
    }
};

/**************************************************** 
 ***    236,Medium,Lowest Common Ancestor of a Binary Tree 
 ****************************************************/

/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4

For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// The tree is not BST, so we can't use value comparison. Instead, we need to examine both subtrees recursively O(n).

// Solution 1. Use two auxiliary vectors storing the search paths from root to the node. 
// Compare the two paths and find the last element both in two paths.

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || !p || !q) return NULL;
        if( !search(root, p, path1) || !search(root, q, path2)) return NULL;
        TreeNode* node = NULL;
        while(!path1.empty() && !path2.empty()) {
            TreeNode* n1 = path1.front(); path1.pop_front();
            TreeNode* n2 = path2.front(); path2.pop_front();
            if(n1 == n2) node = n1;
            else break;
        }
        return node;
    }
    //search p under subtree root
    bool search(TreeNode* root, TreeNode* p, deque<TreeNode*>& path) {
        if(!root) return false;

        path.push_back(root);
        if(root == p) return true;
        //search left and right subtree
        if(search(root->left, p, path) || search(root->right, p, path)) return true;
        path.pop_back(); //retrace
        return false;
    }
    deque<TreeNode*> path1, path2;
};

// Solution 2 without the auxiliary path vector.
// Assumes p and q are not NULL.
// Similar to Solution 1 in that when root is equal to either node, return the root.
// Then call the function for left and right subtrees. If both returns a non NULL value, that means one node is in left sub-tree, and the other is in the right sub-tree. In this case root is the LCA, and we return root.
// In other cases, simply return the value returned by the recursive calls.

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;
        if(root == p || root == q) return root;
        TreeNode* lca_l = lowestCommonAncestor(root->left, p, q);
        TreeNode* lca_r = lowestCommonAncestor(root->right, p, q);
        if(lca_l && lca_r) return root;
        else return (lca_l ? lca_l : lca_r);
    }
};


/**************************************************** 
 ***    230,Medium,Kth Smallest Element in a BST 
 ****************************************************/

/*
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Hint:

    Try to utilize the property of a BST.
    What if you could modify the BST node's structure?
    The optimal runtime complexity is O(height of BST).
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//First find minimum, and store the search path. Then do inorder traversal k times.
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        if(!root) return 0;
        stack<TreeNode*> path;
        while(root) {
            path.push(root);
            root = root->left;
        }
        TreeNode* node(NULL);
        int i = 1;
        while(1) {
            if(path.empty()) return 0;
            node = path.top(); path.pop();
            if(i == k) return node->val;
            i++;
            node = node->right;
            while(node) {
                path.push(node); node = node->left;
            }
        }
        return 0;
    }
};


/**************************************************** 
 ***    221,Medium,Maximal Square 
 ****************************************************/

/*
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing all 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Return 4. 
*/

// Same idea as maximal rectangle, use routine in finding largest rectangle. Except when calculating area, use min(height, length)^2. See solutions in 085 maximal rectangle

class Solution {
public:
    int maximalSquare(vector<vector<char> > &matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> height(n, 0);
        int max_area = 0;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                height[j] = (matrix[i][j] == '1') ? height[j]+1 : 0;
            }
            max_area = max(max_area, largestSquareArea(height));
        }
        return max_area;
    }

    int largestSquareArea(vector<int>& height) {
        if(height.empty()) return 0;
        height.push_back(0);
        deque<int> s; //stack for positions
        int n = height.size();
        int max_area = 0;
        for(int i = 0; i < n; ++i) {
             while(!s.empty() && height[s.back()] > height[i]) {
                int h = height[s.back()];
                s.pop_back();
                int j = s.empty() ? 0 : s.back()+1;
                int side = min(h, i-j);
                max_area = max(max_area, side*side);
            }
            s.push_back(i);
        }
        return max_area;
    }
};

/**************************************************** 
 ***    216,Medium,Combination Sum III 
 ****************************************************/

/*
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Ensure that numbers within the set are sorted in ascending order.

Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]


Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]
*/

/// Solution 1. Recursive solution. Choose number in ascending order, track how many trials we are left, and the next available number to choose.
// Terminate at three conditions:
// 1. Searched beyond number 9.
// 2. Used up all k trials.
// 3. target sum is smaller than the next number i

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int> > result;
        if(k == 0 || n <= 0) return result;
        vector<int> tmp;
        dfs(1, k, n, tmp, result);
    }
    //search starting from i, k numbers left
    void dfs(int i, int k, int target, vector<int>& tmp, vector<vector<int> >& result) {
        if(target == 0 && k == 0) { //target is 0 and we used exactly k numbers
            result.push_back(tmp);
            return;
        }
        if(i == 10 || k < 0 || target < i) return; //used up all numbers or all trials, or target < i.

        tmp.push_back(0);
        for(int j = i; j < 10; ++j) {
            tmp.back() = j;
            dfs(j+1, k-1, target-j, tmp, result);
        }
        tmp.pop_back();
    }
};

// Solution 2. Iterative. Keep a running sum and trial number. The tricky part is how to calculate the partial sums properly. 
// Caveats:
// sum += tmp[i] should be placed after tmp[i] == 10 checks!
// after retracing, need to first subtract the tmp[i] value from sum, so that when tmp[i] is incremented, sum += tmp[i] will give the correct new usm.

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int> > result;
        if(k == 0 || n <= 0) return result;
        vector<int> tmp(k, 0);
        int i = 0; //i-th trial
        int sum = 0;
        while(i >= 0) {
            if(i == k) {
                if(sum == n) result.push_back(tmp); 
                i--; 
                if(i >= 0) sum -= tmp[i]; 
                continue; //retrace
            }
            tmp[i]++;
            if(tmp[i] == 10) { //retrace
                i--; 
                if(i >= 0) sum -= tmp[i]; 
                continue;
            } 
            sum += tmp[i]; //add to sum
            i++;
            if(i < k) tmp[i] = tmp[i-1]; //initialize starting point for next number (for tmp[i]++).
        }
        return result;
    }
};



/**************************************************** 
 ***    213,Medium,House Robber II 
 ****************************************************/

/*
Note: This is an extension of House Robber.

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/

// One pass DP solution. Use two variables, one meaning maximum including first house, second meaning maximum excluding first house.
// Special treatment for the last house.

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        //dp1: maximum including first house, dp2: maximum excluding first house
        vector<int> dp1(n, 0), dp2(n, 0);
        dp1[0] = nums[0]; dp1[1] = nums[0];
        dp2[0] = 0; dp2[1] = nums[1];
        for (int i = 2; i < n-1; ++i) {
            dp1[i] = max(dp1[i-2] + nums[i], dp1[i-1]); 
            dp2[i] = max(dp2[i-2] + nums[i], dp2[i-1]); 
        }
        //last one
        dp1[n-1] = dp1[n-2];
        dp2[n-1] = max(dp2[n-3] + nums[n-1], dp2[n-2]); 
        return max(dp1[n-1], dp2[n-1]);
    }
};

/// Two pass DP solution. Each pass calls original rob, once excluding nums[0] and once excluding nums[n-1]. Compare the two and return the maximum
/// robLin is the original rob function on a linear street.

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        return max(robLin(nums.begin(), nums.end()-1), robLin(nums.begin()+1, nums.end()));
    }
    int robLin(vector<int>::const_iterator beg, vector<int>::const_iterator end) {
        int n = end - beg;
        if(n == 0) return 0;
        if(n == 1) return *beg;
        if(n == 2) return max(*beg, *(beg+1));
        int last = max(*beg, *(beg+1));
        int lastlast = *beg;
        int curr = 0;
        for(vector<int>::const_iterator it = beg+2; it != end; it++) {
            curr = max(lastlast + *it, last);
            lastlast = last;
            last = curr;
        }
        return curr;
    }
};


/**************************************************** 
 ***    209,Medium,Minimum Size Subarray Sum 
 ****************************************************/

/*
Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

click to show more practice.
More practice:

If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).
*/

/// Solution 1: sliding window. Move one step further to optimize. O(n)

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int sum = 0, minL = INT_MAX;
        for(int i = 0, istart = 0; i < n; ++i) {
            sum += nums[i];
            if(sum < s) continue;
            while(sum - nums[istart] >= s) {
                sum -= nums[istart++];
            }
            minL = min(minL, i-istart+1);
            sum -= nums[istart++]; //move one step further
        }
        return minL != INT_MAX ? minL : 0;
    }
};

/// Solution 2: binary search on the accumulative sums. O(nlogn)
// First create the partial sum array, then scan the sum, if the paritial_sum >= s, then we search for the array before the element and find the largest element <= (partial_sum - s). Use binary search
// Since all numbers are positive, if we see partial_sum == s, we can skip the binary search and use i+1 as the length (can't be shorter than nums[0..i].

/// So far, divide and conquer seems not possible...

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.empty()) return 0;
        //get partial sums
        int n = nums.size();
        vector<int> partial(n, 0);
        partial[0] = nums[0];
        int minL = INT_MAX;
        for(int i = 1; i < n; ++i) {
            partial[i] = partial[i-1] + nums[i];
        }
        for(int i = 0; i < n; ++i) {
            if(partial[i] >= s) {
                //binary search for largest number <= residue in sums[0, i-1];
                int residue = partial[i] - s;
                int lo = 0, hi = i-1, mid = 0;
                while(lo <= hi) {
                    mid = lo + (hi - lo) / 2;
                    if(partial[mid] <= residue) lo = mid+1;
                    else hi = mid-1;
                }
                minL = min(minL, i-hi);
            }
        }
        return minL == INT_MAX ? 0 : minL;
    }
};


/**************************************************** 
 ***    208,Medium,Implement Trie (Prefix Tree) 
 ****************************************************/

/*
Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z. 
*/

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");

/// Solution 1, simpler, with delete function (which slows down runtime by 40 ms!)

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
        isKey = false;
        links.resize(26, NULL);
    }

    bool isKey;
    vector<TrieNode*> links;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        eraseUtil(root);
    }
    // Inserts a word into the trie.
    void insert(string word) {
        insertUtil(root, word, 0);
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode* node = searchUtil(root, word, 0);
        return node != NULL && node->isKey;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* node = searchUtil(root, prefix, 0);
        return node != NULL;
    }

private:
    //root can never be NULL
    void insertUtil(TrieNode* root, const string& word, int i) {
        if(i == word.size()) { root->isKey = true; return; }
        int c = word[i] - 'a';
        if(!root->links[c]) root->links[c] = new TrieNode();
        insertUtil(root->links[c], word, i+1);
    }
    TrieNode* searchUtil(TrieNode* root, const string& word, int i) {
        if(root == NULL) return NULL;
        if(i == word.size()) return root;
        int c = word[i] - 'a';
        return searchUtil(root->links[c], word, i+1);
    }
    void eraseUtil(TrieNode* root) {
        if(!root) return;
        for(int c = 0; c < 26; ++c) eraseUtil(root->links[c]);
        delete root;
    }
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");


/// Solution 2, slightly different.

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
        links = new TrieNode*[26];
        for (int i = 0; i < 26; ++i)
            links[i] = NULL;
        isKey = false;
    }
    
    TrieNode** links; //array of pointers
    bool isKey;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        root = insert(root, word, 0);
    }

    TrieNode* insert(TrieNode* x, string word, int d) {
        if (x == NULL) { x = new TrieNode(); }
        if (d == word.size()) x->isKey = true;
        else {
            int i = word[d] - 'a';
            x->links[i] = insert(x->links[i], word, d+1);
        }
        return x;
    }
    
    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode *x = search(root, word, 0);
        return (x != NULL && x->isKey);
    }
    
    TrieNode* search(TrieNode* x, string word, int d) {
        if (x == NULL) return NULL;
        if (d == word.length()) return x;
        int i = word[d] -'a';
        return search(x->links[i], word, d+1);
    }
    
    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* x = search(root, prefix, 0);
        return x != NULL;
    }
    
private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");

/**************************************************** 
 ***    200,Medium,Number of Islands 
 ****************************************************/

/*
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000

Answer: 1

Example 2:

11000
11000
00100
00011

Answer: 3
*/

//Solution 1: Standard DFS
// Note that we have to check 4 neighbors! Only checking right and bottom is not enough! See the case below:

// 1 1 1
// 0 1 0
// 1 1 1
// Starting from left top corner, if only checking 2 neighbors, we missed the bottom left one, and we end up count = 2.

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        for(int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(grid[i][j] == '1') {
                    dfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
    void dfs(vector<vector<char> >& grid, int i, int j) {
        grid[i][j] = '0';
        //check 4 neighbors
        if(i > 0 && grid[i-1][j] == '1') dfs(grid, i-1, j); //top
        if(j > 0 && grid[i][j-1] == '1') dfs(grid, i, j-1); //left
        if(i < grid.size()-1    && grid[i+1][j] == '1') dfs(grid, i+1, j); //bottom
        if(j < grid[i].size()-1 && grid[i][j+1] == '1') dfs(grid, i, j+1); //right
    }
};

// Solution 2: BFS using a queue
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        for(int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(grid[i][j] == '1') {
                    bfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
    void bfs(vector<vector<char> >& grid, int i, int j) {
        deque<pair<int, int> > q;
        q.push_back(make_pair(i, j)); 
        grid[i][j] = '0';
        while (!q.empty()) {
            int ni = q.front().first;
            int nj = q.front().second;
            q.pop_front();
            //check 4 neighbors
            if(ni > 0 && grid[ni-1][nj] == '1') { grid[ni-1][nj] = '0'; q.push_back(make_pair(ni-1, nj)); } //top
            if(nj > 0 && grid[ni][nj-1] == '1') { grid[ni][nj-1] = '0'; q.push_back(make_pair(ni, nj-1)); } //left
            if(ni < grid.size()-1    && grid[ni+1][nj] == '1') { grid[ni+1][nj] = '0'; q.push_back(make_pair(ni+1, nj)); } //bottom
            if(nj < grid[ni].size()-1 && grid[ni][nj+1] == '1') { grid[ni][nj+1] = '0'; q.push_back(make_pair(ni, nj+1)); } //right
        }
    }
};

// Solution 3: Union find.
// Record the total number of disjoint sets. m*n elements, initially all inactive. Scan the grid, when finding a '1', mark the element as active, and set its id and size attributes in UnionFind class. Maintain a conversion formula from 2D positions to 1D index (i*n+j).
// Use weighted union find with path compression, close to O(n) time complexity.
// Caveats:
// 1. 1D index is i*n+j, not i*m+j!
// 2. we need to check left and top neighbors, can skip bottom and right neighbors. Since we are scanning strictly top-down, left-right. 

class UnionFind {
public:
    UnionFind(int N) : n(0) {
        id.resize(N, -1);
        size.resize(N, 0);
    }
    //add element i as a new set
    void add(int i) {
        id[i] = i;
        size[i] = 1;
        n++;
    }
    //unite two elements
    void unite(int i, int j) {
        while(id[i] != i) { id[i] = id[id[i]]; i = id[i]; }
        while(id[j] != j) { id[j] = id[id[j]]; j = id[j]; }
        if(i != j) {
            if(size[i] < size[j]) { id[i] = j; size[j] += size[i]; }
            else { id[j] = i; size[i] += size[j]; }
            n--;
        }
    }

    int count() const { return n; }

private:
    vector<int> id; //set id
    vector<int> size; //size of each set
    int n; //total number of sets
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        UnionFind uf(m*n);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == '0') continue;
                int idx = i*n+j;
                uf.add(idx); //add to sets
                if(i > 0 && grid[i-1][j] == '1')  //top neighbor
                    uf.unite(idx, idx-n);
                if(j > 0 && grid[i][j-1] == '1') //left neighbor
                    uf.unite(idx, idx-1);
            }
        }
        return uf.count();        
    }
};


/**************************************************** 
 ***    187,Medium,Repeated DNA Sequences 
 ****************************************************/

/// Similar approach to solution 1, except we use 2-digit code for each character, thus resulting in 20-bit hash code for 
/// the substring, represented by an integer (32 bits). 
/// Use a function to return the hash code for the 4 characters, we only requires 2 bits
/// First calculate the hash code for the first 9 digit, when we add a new digit, we multiply by 4 (radix-4 hash code), or
/// equivalently, << 2. How to strip off the highest character when moving to next? Notice that we only have 20 bits, and 
/// we simply turn off the highest 12 bits, so we mask with Ox000FFFFF.

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ret;
        int n = s.size();
        if(n < 10) return ret;
        map<int, int> count;
        int hash = 0;
        for(int i = 0; i < 9; ++i) {
            int v = char2num(s[i]);
            hash = (hash << 2) | v;
        }
        for(int i = 9; i < n; ++i) {
            int v = char2num(s[i]);
            hash = (hash << 2) & 0x000FFFFF | v;
            count[hash]++;
            if(count[hash] == 2) ret.push_back(s.substr(i-9, 10));
        }
        return ret;
    }
    
    int char2num(char c) {
        if      (c == 'A') return 0;
        else if (c == 'C') return 1;
        else if (c == 'G') return 2;
        else               return 3;
    }
};
/*
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].
*/

/// Use a hash code for the length-10 substring. 3 digit code for each character, so that a total of 30 digits, 
/// which can be represented by an integer (32 bits). 
/// Only 4 characters occuring, 'A', 'C', 'G', 'T' has different last three digits, thus use last three digits (c & 0b111)
/// First calculate the hash code for the first 9 digit, when we add a new digit, we multiply by 8 (radix-8 hash code), or
/// equivalently, << 3. How to strip off the highest character when moving to next? Notice that we only have 30 bits, and 
/// we simply turn off the highest 2 bits, so that we mask with Ox3FFFFFFF.

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ret;
        int n = s.size();
        if(n < 10) return ret;
        map<int, int> count;
        int hash = 0;
        for(int i = 0; i < 9; ++i) {
            hash = (hash << 3) | (s[i] & 7);
        }
        for(int i = 9; i < n; ++i) {
            hash = ((hash << 3) & 0x3FFFFFFF) | (s[i] & 7);
            count[hash]++;
            if(count[hash] == 2) ret.push_back(s.substr(i-9, 10));
        }
        return ret;
    }
};

/// Similar approach to solution 1, except we use 2-digit code for each character, thus resulting in 20-bit hash code for 
/// the substring, represented by an integer (32 bits). 
/// Use a function to return the hash code for the 4 characters, we only requires 2 bits. We can use a trick to return the hash value:
/// hash = (s[i] - 'A' + 1) % 5. This way, ACGT returns 1 3 2 0 respectively.

/// First calculate the hash code for the first 9 digit, when we add a new digit, we multiply by 4 (radix-4 hash code), or
/// equivalently, << 2. How to strip off the highest character when moving to next? Notice that we only have 20 bits, and 
/// we simply turn off the highest 12 bits, so we mask with Ox000FFFFF.

// Another optimization is to use an array to store the hash table (can use char if counts are less than 256 to save space). Note that using vector<int> increases runtime from 20 ms to 100 ms. But using vector<char> is only 12 ms.

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> result;
        char dict[1048576] = {0}; //hash => counts (assume counts < 256).
        int n = s.size();
        const int LEN = 10;
        if(n <= LEN) return result;
        int hashval = 0;
        for(int i = 0; i < LEN-1; ++i) {
            hashval = (hashval << 2) | (s[i] - 'A' + 1) % 5;
        }
        for(int i = LEN-1; i < n; ++i) {
            //remove two leading bits, and shift to right by two and add next hash value
            hashval = ((hashval << 2) & 0x000FFFFF) | (s[i] - 'A' + 1) % 5;
            if(dict[hashval]++ == 1) result.push_back(s.substr(i-LEN+1, LEN));
        }
        return result;
    }
};


/**************************************************** 
 ***    186,Medium,Reverse Words in a String II 
 ****************************************************/

/*
Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.

The input string does not contain leading or trailing spaces and the words are always separated by a single space.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Could you do it in-place without allocating extra space?

Related problem: Rotate Array
*/

// Solution: first reverse the whole string, then scan left to right to reverse each individual words.
// Two pointers.

class Solution {
public:
    void reverseWords(string &s) {
        int n = s.size();
        if(n <= 1) return;
        reverse(s, 0, n);
        int i = 0, j = 0;
        for(int i = 0; i < n;) {
            j = i+1;
            while(j < n && s[j] != ' ') j++;
            reverse(s, i, j); //j points to space
            i = j+1;
        }
    }
    //reverse s[lo, hi)
    void reverse(string &s, int lo, int hi) {
        hi--;
        while(lo < hi) {
            char c = s[lo];
            s[lo] = s[hi];
            s[hi] = c;
            lo++; hi--;
        }
    }
};

/**************************************************** 
 ***    179,Medium,Largest Number 
 ****************************************************/

/*
Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.
*/

// Write a customized comparator function to compare two integer string, compare a+b v.s. b+a;
// An improved version from comparing integers, where we need to do int=>string conversions many times.
// Use a comparator class. can also define a bool compare function outside the class.

// Caveats:
// Corner case where nums are filled with "0"s, so we need to check if first character of result is zero.

class Solution {
public:
    struct myClass {
        bool operator() (const string& a, const string& b) {
            return a + b < b + a;
        }
    } compare;

    string largestNumber(vector<int>& nums) {
        string res;
        //assemble res from reverse iteration
        int n = nums.size();
        vector<string> strs(n);
        for(int i = 0; i < n; ++i)  strs[i] = num2str(nums[i]);

        sort(strs.begin(), strs.end(), compare);
        
        for(int i = n-1; i >= 0; --i) {
            res += strs[i];
        }
        if(res[0] == '0') return "0";
        else return res;
    }
    
    string num2str(int num) {
        if(num == 0) return "0";
        string res;
        while(num) {
            int d = num % 10;
            res = char(d + '0') + res;
            num /= 10;
        }
        return res;
    }
};

/**************************************************** 
 ***    173,Medium,Binary Search Tree Iterator 
 ****************************************************/

/*
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree. 
*/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

// Push all left spline to a stack.
// When popping, it a node has right subtree, push all left spline of the right child.

class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        pushLeft(root, s);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *node = s.back();
        int val = node->val;
        s.pop_back();
        if(node->right) pushLeft(node->right, s);
        return val;
    }
private:
    void pushLeft(TreeNode *root, deque<TreeNode*>& s) {
        while(root) {
            s.push_back(root);
            root = root->left;
        }
    }
    deque<TreeNode*> s; //stack
};


/**************************************************** 
 ***    167,Medium,Two Sum II - Input array is sorted 
 ****************************************************/

/*
Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2 
*/

// Solution: two pointers, linear search. Time O(n), space O(1).

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
      vector<int> ret(2, -1);
      int n = numbers.size();
      int i = 0, j = n-1;
      while(i < j) {
        int sum = numbers[i] + numbers[j];
        if(sum > target) j--;
        else if(sum < target) i++;
        else {
          ret[0] = i+1; ret[1] = j+1;
          return ret;
        }
      }
      return ret;
    }
};

/**************************************************** 
 ***    162,Medium,Find Peak Element 
 ****************************************************/

/*
A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

click to show spoilers.
Note:

Your solution should be in logarithmic complexity.
*/

// Solution 1. Simple binary search. compare mid with mid+1. break when lo == hi.

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int lo = 0, hi = n-1;
        while(lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if(nums[mid] < nums[mid+1]) lo = mid+1;
            else hi = mid;
        }
        return lo;
    }
};

// Solution 2. Variant of solution 1. Slightly more complicated. Need to compare mid with mid-1 and mid+1.

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        if(n == 1) return 0;
        if(nums[0] > nums[1]) return 0;
        if(nums[n-1] > nums[n-2]) return n-1;
        int lo = 1, hi = n-2;
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            if(nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]) return mid;
            else if(nums[mid] < nums[mid-1]) hi = mid-1;
            else lo = mid+1;
        }
        return lo;
    }
};


/**************************************************** 
 ***    161,Medium,One Edit Distance 
 ****************************************************/

/*
Given two strings S and T, determine if they are both one edit distance apart.
*/

/*
one pass solution. Two pointers scanning two arrays.
For s[i] and t[j], If found equal, move forward,
if not equal, then the rest should be the same, three cases:
a) remove s[i] and the rest matches, so we just check isSame for s[i+1, m) and t[j, n). e.g.
   abc[de]   ab[de]
     i          j
b) insert t[j] and the rest matches, so we just check isSame for s[i, m) and t[j+1, n) e.g
   ab[efg]   abd[efg]
      i        j
c) replace s[i] with t[j] and the rest matches, so we just check isSame for s[i+1, m) and t[j+1, n) e.g.
   abe[fg]   abc[fg]
     i         j

Finally, if we break out of loop, which means everything seen so far is matched. We simply check if we still have one and only one unchecked character in either one of the two arrays.

*/

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int m = s.size(), n = t.size();
        if(m - n < -1 || m -n > 1) return false;
        int i = 0, j = 0;
        while(i < m && j < n) {
            if(s[i] == t[j]) { i++; j++; }
            else return isSame(s, i+1, t, j) || isSame(s, i, t, j+1) || isSame(s, i+1, t, j+1);
        }
        return j == n-1 || i == m-1;
    }
    bool isSame(const string& s, int i, const string& t, int j) {
        int m = s.size(), n = t.size();
        while(i < m && j < n) {
            if(s[i] != t[j]) return false;
            i++; j++;
        }
        return i == m && j == n;
    }
};


/**************************************************** 
 ***    153,Medium,Find Minimum in Rotated Sorted Array 
 ****************************************************/

/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.
*/

/*
General solution that also works for duplicated cases.
Binary search. The array can be broken into two parts, 
for example, [4 5 6 7 0 1 2], first part is 4-7, second part is 0-2. If array is unrotated, then only first part exists (corner case). 

There are three anchor points, lo, hi, and mid. Compare nums[mid] with nums[hi].
1. If nums[mid] < nums[hi], then we know for sure that minimum lies on or before mid, so hi = mid (we excluding nums[mid+1, hi]).
2. If nums[mid] > nums[hi], then we know for sure that mid is in first part of array, and array is rotated. This means that minimum lies between mid and hi, so lo = mid+1. Since nums[mid] > nums[hi], nums[mid] cannot be the minimum, so we can exlude it. 
3. If nums[mid] = nums[hi], we can't say where mid lies. It could be left or right. But we can safely exclude nums[hi], since it is a duplicated entry apart from nums[mid]. Thus we simply decrement hi. 
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo = 0, hi = nums.size()-1;
        int mid = 0;
        //invariant: [lo, hi] contains minimum
        while(lo < hi) {
            mid = lo + (hi-lo)/2;
            if(nums[mid] < nums[hi]) hi = mid;
            else if(nums[mid] > nums[hi]) lo = mid+1;
            else hi--;
        }
        return nums[lo];
    }
};

/**************************************************** 
 ***    152,Medium,Maximum Product Subarray 
 ****************************************************/

/*
Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6. 
*/

// DP solution.
// Keep track of maximum (in terms of absolute value) positive and negative values (initially set as 0)
// Update the values based on the polarity of newly seen element. If max_pos_prod and max_neg_prod are 0, then they are considered uninitialized.
// Caveat: When updating max_pos and max_neg, need to use temporary variables
// Optimization: since we call nums[i] multiply times, save it into a variable x to avoid excessive array indexing cost.

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int max_pos_prod = 0, max_neg_prod = 0, max_prod = INT_MIN;
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if(x == 0) {
                max_prod = max(max_prod, 0);
                max_pos_prod = max_neg_prod = 0;
            } else if(x > 0) {
                max_pos_prod = (max_pos_prod > 0) ? max_pos_prod*x : x;
                max_neg_prod = (max_neg_prod < 0) ? max_neg_prod*x : 0;
            } else { //nums[i] < 0
                int tmp_pos = max_pos_prod, tmp_neg = max_neg_prod;
                max_pos_prod = (tmp_neg < 0) ? tmp_neg*x : 0;
                max_neg_prod = (tmp_pos > 0) ? tmp_pos*x : x;
            }
            if(max_pos_prod > 0 && max_prod < max_pos_prod) max_prod = max_pos_prod;
            if(max_neg_prod < 0 && max_prod < max_neg_prod) max_prod = max_neg_prod; //needed for n=1 case with one negative number (max_pos undefined)
        }
        return max_prod;
    }
};

// A slightly different solution, considering n=1 corner case explicitly (so that max_pos will always be valid)
// Corner case: when there is only one negative number, should return itself, not 0.

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0]; //corner case
        int max_pos(0), max_neg(0), max_prod(0);
        int tmp_pos(0), tmp_neg(0);
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if(x == 0) tmp_pos = tmp_neg = 0;
            else if (x > 0) {
                tmp_pos = (max_pos > 0) ? max_pos*x : x;
                tmp_neg = (max_neg < 0) ? max_neg*x : 0;
            } else {  //x < 0
                tmp_pos = (max_neg < 0) ? max_neg*x : 0;
                tmp_neg = (max_pos > 0) ? max_pos*x : x;
            }
            max_pos = tmp_pos; max_neg = tmp_neg;
            max_prod = max(max_prod, max_pos);
        }
        return max_prod;
    }
};

/**************************************************** 
 ***    151,Medium,Reverse Words in a String 
 ****************************************************/

/*
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Update (2015-02-12):
For C programmers: Try to solve it in-place in O(1) space.

click to show clarification.
Clarification:

    What constitutes a word?
    A sequence of non-space characters constitutes a word.
    Could the input string contain leading or trailing spaces?
    Yes. However, your reversed string should not contain leading or trailing spaces.
    How about multiple spaces between two words?
    Reduce them to a single space in the reversed string.
*/

// Solution 1: kinda in-place. Procedure:
// 1. remove extra spaces and store the shorted string to s[0, end)
// 2. reverse substring s[0, end)
// 3. reverse individual string in s[0, end)
// Two pointers

class Solution {
public:
    void reverseWords(string &s) {
        if(s.empty()) return;
        int n = s.size();
        //1. remove extra spaces
        //end: end of shorted string, scan j
        int i = 0, j = 0;
        int beg = 0, end = 0;
        while(beg < n && s[beg] == ' ') beg++; 
        //beg points to first non-space char or end
        end = 0; //copy string to start
        for(j = beg; j < n; j++) {
            if(s[j] == ' ') continue;
            else { //non-space character, copy
                if(j > beg && s[j-1] == ' ') s[end++] = ' '; //add space
                s[end++] = s[j];
            }
        }
        //2. reverse substr string s[0, end)
        reverse(s, 0, end);
        
        //3. reverse individual words for s[0, end)
        for(i = 0; i < end; i++) {
            if(s[i] == ' ') continue;
            j = i+1;
            while(j < end && s[j] != ' ') j++;
            reverse(s, i, j); //j points to space or s.end()
            i = j;
        }
        s = s.substr(0, end); //copy result to s (can handle end = 0 case)
    }

    //reverse s[lo, hi)
    void reverse(string &s, int lo, int hi) {
        hi--;
        while(lo < hi) {
            char c = s[lo];
            s[lo] = s[hi];
            s[hi] = c;
            lo++; hi--;
        }
    }
};

// Solution 2: Use an auxiliary string vector
// Caveat: size_t i = str.size()-1 is wrong! because it will fail when str is empty(), use int i instead.

class Solution {
public:
    void reverseWords(string &s) {
        vector<string> strs;
        split(s, strs);
        s.clear();
        for (int i = strs.size()-1; i >= 0; i--) {
            s += strs[i];
            if(i > 0) s += " ";
        }
    }
    void split(string& s, vector<string>& strs) {
        s += " ";
        string word;
        for(size_t i = 0; i < s.size(); ++i) {
            char c = s[i];
            if(c != ' ') word += c;
            else if(word != "") {
                strs.push_back(word);
                word = "";
            }
        }
    }
};

/**************************************************** 
 ***    148,Medium,Sort List 
 ****************************************************/

/*
Sort a linked list in O(n log n) time using constant space complexity.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution 1. Top-down merge sort (not really constant space, because of stack space)
// when finding the middle element, fast is initialized as head->next, not head, to avoid infinite loop in corner cases (only two nodes).

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* p = head, *q = head;
        while(q->next && q->next->next) {
            p = p->next;
            q = q->next->next;
        }
        //merge head and p->next
        q = p->next;
        p->next = NULL;
        head = sortList(head);
        q = sortList(q);
        return merge(head, q);
    }

    ListNode *merge(ListNode* left, ListNode *right) {
        ListNode* dummy = new ListNode(0);
        ListNode *p = left, *q = right, *tail = dummy;
        while(p && q) {
            if(p->val <= q->val) {
                tail->next = p; p = p->next;
            } else {
                tail->next = q; q = q->next;
            }
            tail = tail->next;
        }
        tail->next = p ? p : q;

        p = dummy->next;
        delete dummy;
        return p;
    }
};

// Solution 2. Bottom-up merge sort with O(1) space, by using an elegant split function.
// Maintain the length of sub lists to be sorted, starting form 1, and then 2, 4 ...
// Split(head, len), cuts break the list at position len, and returns the head of the second part, e.g.
// head = 1 -> 2 -> 3 -> 4, len = 2, then after second = split(head, 2), we have head = 1->2,  second = 3->4.
// Merge merges to linked lists and attach them to the head, and then returns the tail of the merged list.

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        int count = 0;
        ListNode *p = dummy->next;
        while(p) {
            count++;
            p = p->next;
        }
        for(int len = 1; len < count; len *= 2) { //len: merge length
            ListNode *tail = dummy, *left = dummy->next;
            while(left) {
                ListNode *right = split(left, len);
                ListNode *next = split(right, len);
                tail = merge(left, right, tail);
                left = next;
            }
        }
        head = dummy->next;
        delete dummy;
        return head;
    }

    ListNode* split(ListNode *head, int len) {
        while(head && len > 1) {
           head = head->next; len--;
        }
        if(!head) return NULL;
        ListNode *second = head->next;
        head->next = NULL;
        return second;
    }
    //merge two lists and attach to head (head serves similar to the dummy head), and return the tail of the merged list
    ListNode *merge(ListNode* left, ListNode *right, ListNode *head) {
        ListNode *p = left, *q = right, *tail = head;
        while(p && q) {
            if(p->val < q->val) {
                tail->next = p; p = p->next;
            } else {
                tail->next = q; q = q->next;
            }
            tail = tail->next;
        }
        tail->next = p ? p : q;
        while(tail->next) tail = tail->next;
        return tail;
    }
};

// Solution 3. 3-way quick-sort, with the first element as the pivot. Maintain three sub lists, one < x, one == x, one > x. Then attach them ogether in the end. Not really O(1) space, due to recursive calls.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        return sortList(head, NULL);
    }
    //sort list and connect it to next, return new head
    ListNode* sortList(ListNode *head, ListNode *next) {
        ListNode* dummy = new ListNode(0);
        //use head as pivot. p : <x, q : >x, r : =x
        ListNode *phead = NULL, *qhead = NULL, *rhead = NULL;
        ListNode *p = NULL, *q = NULL, *r = head;
        ListNode *curr = head->next;
        while(curr) {
            if(curr->val < head->val) {
                if(!p) p = phead = curr;
                else p = p->next = curr;
            } else if(curr->val > head->val) {
                if(!q) q = qhead = curr;
                else q = q->next = curr;
            } else {
                r = r->next = curr;
            }
            curr = curr->next;
        }
        //work on first part (<x)
        if(phead) {
            p->next = NULL; //p is tail
            dummy->next = sortList(phead, head);
        } else dummy->next = head;
        //work on second part (>x)
        if(qhead) {
            q->next = NULL; //q is tail
            r->next = sortList(qhead, next);
        } else r->next = next;
        head = dummy->next;
        delete dummy;
        return head;
    }
};

// Solution 4. Bottom-up merge sort, using a queue. O(n) space!
// Sort is unstable if number of nodes are not power of 2!

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        deque<ListNode*> q;
        ListNode *p = head;
        //push nodes into queue, also set next to NULL (break into many single-node lists)
        while(p) {
            q.push_back(p);
            ListNode *next = p->next;
            p->next = NULL;
            p = next;
        }
        ListNode dum(0);
        p = &dum; //dummy node
        while(!q.empty()) {
            ListNode* n1 = q.front(); q.pop_front();
            if(q.empty()) return n1;
            ListNode *n2 = q.front(); q.pop_front();
            q.push_back(merge(n1, n2));
        }
        return NULL; //something wrong
    }
    //merge two sorted, non-empty lists
    ListNode* merge(ListNode *head1, ListNode *head2) {
        ListNode dum(0), *p(&dum), *tail(p);
        while(head1 && head2) {
            if(head1->val <= head2->val) {
                tail->next = head1;
                head1 = head1->next;
            } else {
                tail->next = head2;
                head2 = head2->next;
            }
            tail = tail->next;
        }
        tail->next = head1 ? head1 : head2;
        return p->next;
    }
};


/**************************************************** 
 ***    147,Medium,Insertion Sort List 
 ****************************************************/

/*
Sort a linked list using insertion sort.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// Start from head, track the tail of already sorted list
/// If the element to be added is larger than the tail of sorted list, simply append it to the tail and move on (makes the code more efficient, 92ms => 28ms reduction!)
/// Otherwise scan from head of list and find the position to insert
/// Remember to set the next pointer of list's tail to NULL in the beginning.

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode *tail = head, *q = head->next;
        tail->next = NULL; //set tail's next to NULL
        while(q) {
            ListNode *next = q->next;
            //insert q to list from dummy to tail
            if(q->val >= tail->val) {
                tail = tail->next = q;  //update tail!
		q->next = NULL;
            } else { //search insert position from beginning
                ListNode *curr = dummy->next, *prev = dummy;
                while(curr && curr->val <= q->val) {
                    prev = curr; curr = curr->next;
                }
                prev->next = q; q->next = curr; //insert to list
            }
            q = next; //move forward
        }

        head = dummy->next;
        delete dummy;
        return head;
    }
};

/**************************************************** 
 ***    144,Medium,Binary Tree Preorder Traversal 
 ****************************************************/

/*
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution (easy).

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        preorder(root, ret);
        return ret;
    }
    void preorder(TreeNode *root, vector<int>& ret) {
        if(!root) return;
        ret.push_back(root->val);
        preorder(root->left, ret);
        preorder(root->right, ret);
    }
};

// Iterative solution using a stack

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        deque<TreeNode*> s; //stack
        s.push_back(root);
        while(!s.empty()) {
            TreeNode *node = s.back(); s.pop_back();
            ret.push_back(node->val);
            if(node->right) s.push_back(node->right);
            if(node->left) s.push_back(node->left);
        }
        return ret;
    }
};

/**************************************************** 
 ***    143,Medium,Reorder List 
 ****************************************************/

/*
Given a singly linked list L: L0->L1->...->Ln-1->Ln,
reorder it to: L0->Ln->L1->Ln-1->L2->Ln-2->...

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 1. Traverse list using a slow and a fast pointer, find the middle element
// 2. Reverse the second half of list and return its head
// 3. start from head of first half, insert elements of second half one-by-one to first half.
// 4. set the next pointer of combined graph's tail as NULL

class Solution {
public:
    void reorderList(ListNode* head) {
        if(!head || !head->next || !head->next->next) return;
        ListNode* slow = head, *fast = head;
        while(fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *p = head;
        ListNode *q = reverse(slow->next);
        slow->next = NULL;
        merge(p, q);
    }

    ListNode* reverse(ListNode *head) {
        if(!head || !head->next) return head;
        ListNode *p = head, *q = p->next;
        //p is head of new list
        while(q) {
            ListNode *tmp = q->next;
            q->next = p;
            p = q; q = tmp; //move forward
        }
        head->next = NULL;
        return p;
    }

    void merge(ListNode* p, ListNode *q) {
        ListNode *r = p;
        while(q) {
            ListNode *tmp = q->next;
            q->next = r->next;
            r->next = q;
            r = q->next; q = tmp; //move forward
        }
    }
};


/**************************************************** 
 ***    139,Medium,Word Break 
 ****************************************************/

/*
 Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code". 
*/

/// Dynamic programming, store whether s's length-i substring can be broken into an array. 
/// When found, just break;
/// Optimization: for j goes opposite direction to i, so that we encountered lastly found breakable item first.
/// 4ms.

class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        //if(s.empty()) return true;
        int n = s.size();
        vector<bool> breakable(n+1, false); //whether s[i, n) is breakable
        breakable[n] = true; //s[n, n) is defined to be true
        for(int i = n-1; i >= 0; --i) { //check s[i, n)
            for(int j = i+1; j <= n; ++j) { //check s[i, j) and s[j, n), j direction optimized so that we encountered lastly set breakable[j] first
                if(breakable[j] && wordDict.count(s.substr(i, j-i))) { 
                    breakable[i] = true; 
                    break; 
                }
            }
        }
        return breakable[0];        
    }
};

// Solution 2. Same solution as 1 except starting from beginning
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1,false);
        dp[0]=true;
        for(int i=1; i<=n; i++)  {
            for(int j = i-1; j >= 0; j--) {
                if(dp[j] && wordDict.count(s.substr(j,i-j))) {
                    dp[i]=true;
                    break; //next i
                }
            }
        }
        return dp[n];
    }
};

// Solution 3. DP with memoization
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        if(breakable.count(s)) return breakable[s];
        if(wordDict.count(s)) {
            breakable[s] = true; //memoization
            return true;
        }
        int n = s.size();
        for(int i = 1; i < n; ++i) {
            if(wordDict.count(s.substr(0, i)) && wordBreak(s.substr(i), wordDict)) {
                breakable[s] = true;
                return true;
            }
        }
        breakable[s] = false;
        return false;
    }
    unordered_map<string, bool> breakable;
};


/**************************************************** 
 ***    134,Medium,Gas Station 
 ****************************************************/

/*
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique. 
*/

/*
Two pass DP solution using an auxiliary array to store minimum required gas from 0 to other sites. O(n) space.
To be able to complete circuit at a site i, we need to traverse i to 0, and then from 0 to i. The idea is to first figure out
the minimum amount of gas needed when traveling from site 0 to site i (required[i]). 
The second pass, we calculate the remaining gases traveling from site i to 0 (starting with an empty tank). We do it in reverse order.
If at a given site i the remaining gases are larger than the pre-calculated minimum aount of gas needed at that site, then we know for sure that we can complete the circuit at site i.
the net consumption of gas from site i-1 to i is: amount of gas available at site i-1 (gas[i-1]) - gas cost between i-1 and i (cost[i-1]) + leftovers in tank at site i-1 (leftover).
If the net consumption is positive, then the minimum required gas at site i-1 is enough. If it is negative, then we need additional gas to cover the cost from i-1 to i, thus: required[i] = required[i-1] + (net < 0 ? -net : 0);
Similarly, if the net consumption is positive, we have more leftovers, otherwise we have 0. thus: leftover = (net > 0 ? net : 0);
*/

class Solution {
    
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size(); //assume n >= 2
        vector<int> required(n, 0); //minimum required gas from 0 to i
        int leftover(0);  //leftover gas from 0 to i
        for(int i = 1; i < n; ++i) {
            int net = gas[i-1]-cost[i-1]+leftover;
            required[i] = required[i-1] + (net < 0 ? -net : 0);
            leftover = (net > 0 ? net : 0);
        }
        int remaining(0); //leftover from i to 0
        for(int i = n-1; i >= 0; --i) {
           remaining += (gas[i] - cost[i]);
           if(remaining >= required[i]) return i;
        }
        return -1;
    }
};

/*
O(1) space greedy solution. 2 passes.
Start from 0, move forward and record the lowest level in the tank (could be negative), and the associated site position. Say i, this means that, tank will reach lowest level after visiting site i, when reaching site i+1. 
If the lowest level is non-negative, then we can complete circuit at site 0. Just return 0.
Second pass starts form site i+1, and traverse to 0. Calculate the residue amount of gas after reaching 0. If the residue amount is larger than the deficit from 0 to i, then we can complete circle from site i+1.

Caveat:
min_pos+1 need to apply modulo N or not? Looks like not, since that corresponds to site 0, but we already identified site 0 with condition min_left >= 0.
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int leftover = 0, min_left = 0, min_pos = -1;
        for(int i = 0; i < gas.size(); ++i) {
            leftover += gas[i] - cost[i];
            if(leftover < min_left) {  min_left = leftover, min_pos = i; }
        }
        if(min_left >= 0) return 0;
        int residue = 0;
        for(int j = min_pos+1; j < gas.size(); ++j) {
            residue += gas[j] - cost[j];
        }
        if(residue + min_left >= 0) return min_pos+1;
        else return -1;
    }
};

/*
O(1) space greedy solution. Only 1 pass.
We can improve from the last solution by noting that we can calculate residue and leftover in the same loop. When we see a smaller tank level, we reset residue to zero. The calculation for residue is effectively the same as previous solution.
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int leftover = 0, min_left = 0, min_pos = -1, residue = 0;
        for(int i = 0; i < gas.size(); ++i) {
            int net = gas[i] - cost[i];
            leftover += net;
            residue += net;
            if(leftover < min_left) { 
                min_left = leftover;
                min_pos = i; 
                residue = 0;
            } 
        }
        if(residue + min_left >= 0) return (min_pos+1)%gas.size();
        else return -1;
    }
};


/**************************************************** 
 ***    129,Medium,Sum Root to Leaf Numbers 
 ****************************************************/

/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3

The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Post-order traversal using a stack.
// Keep a running partial sum, and when reaching a leaf, add the partial sum to total sum.
// First time visiting a node, add value to partial sum. When finished processing left and right subtrees, remove the value from partial sum.
// Caveats: avoid adding value to partial sum multiple times! Only do it when tag == 0.

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        int partial_sum(0), total_sum(0);
        deque<pair<TreeNode*, int> > s; //stack
        s.push_back(make_pair(root, 0));
        while(!s.empty()) {
            TreeNode *node = s.back().first;
            int tag = s.back().second;
            if(tag == 0) { //first-time, push left subtree to stack
                partial_sum = partial_sum*10 + node->val; //also calculate partial sum
                s.back().second++;
                if(node->left) s.push_back(make_pair(node->left, 0));
            } else if(tag == 1) { //second-time, push right subtree to stack
                s.back().second++;
                if(node->right) s.push_back(make_pair(node->right, 0));
            } else {  //third-time, process node
                if(!node->left && !node->right) total_sum += partial_sum;
                partial_sum /= 10; //revert to previous value without this node
                s.pop_back();
            }
        }
        return total_sum;
    }
};

// Another solution. Similar, but add pathSums when node has been added.
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        stack<pair<TreeNode*, int> > st;
        st.push(make_pair(root, 0));
        int sum = 0, pathSum = root->val;
        while(!st.empty()) {
            TreeNode* node = st.top().first;
            int tag = st.top().second;
            if(tag == 0) {
                st.top().second++;
                if(node->left) { 
                    st.push(make_pair(node->left, 0));
                    pathSum = pathSum*10 + node->left->val;
                }
            } else if(tag == 1) {
                st.top().second++;
                if(node->right) {
                    st.push(make_pair(node->right, 0));
                    pathSum = pathSum*10 + node->right->val;
                }
            } else {
                st.pop();
                if(!node->left && !node->right) sum += pathSum; //leaf node, add to sum
                pathSum /= 10;
            }
        }
        return sum;
    }
};


/**************************************************** 
 ***    127,Medium,Word Ladder 
 ****************************************************/

/*
Given two words (beginWord and endWord), and a dictionary, find the length of shortest transformation sequence from beginWord to endWord, such that:

    Only one letter can be changed at a time
    Each intermediate word must exist in the dictionary

For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]

As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:

    Return 0 if there is no such transformation sequence.
    All words have the same length.
    All words contain only lowercase alphabetic characters.

*/

/* 
=== Solution 1 ===
One-way BFS from beinWord to endWord. Do not remove elements from the original dictionary! Rather create a new one (unvisited) and remove from it.
Systematically trying the new word by altering one character of the new word. Do not create a new string, rather change the character in-place and revert back to original afterwards.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
       deque<pair<string, int> > q;
       unordered_set<string> unvisited = wordList;
       int wl = beginWord.size();

       q.push_back(make_pair(beginWord, 1));
       unvisited.erase(beginWord); //remove beginWord to unvisited
       unvisited.insert(endWord); //insert beginWord to unvisited
       while(!q.empty()) {
           string wd = q.front().first;
           int level = q.front().second;
           if(wd == endWord) return level;
           q.pop_front();
           for(int i = 0; i < wl; ++i) {
               char c = wd[i];
               for(char ch = 'a'; ch <= 'z'; ++ch) {
                   if(ch == c) continue;
                   wd[i] = ch;
                   if(unvisited.count(wd))  {
                       q.push_back(make_pair(wd, level+1));
                       unvisited.erase(wd);
                   }
               }
               wd[i] = c; //revert back
           }
       }

       return 0;
    }
};

/*
=== Solution 2 ===
BFS with two sets, one for current level, one for next level, and in the end of each iteration swap the two.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
       vector<string> current, next;
       int level = 1;
       unordered_set<string> unvisited = wordList;
       int wl = beginWord.size();

       unvisited.erase(beginWord);
       unvisited.insert(endWord);

       current.push_back(beginWord);
       
       while(!current.empty()) {
           for(vector<string>::iterator it = current.begin(); it != current.end(); ++it) {
               string wd = *it;
               for(int i = 0; i < wl; ++i) {
                   char c = wd[i];
                   for(char ch = 'a'; ch <= 'z'; ++ch) {
                       if(ch == c) continue;
                       wd[i] = ch;
                       if(wd == endWord) return level+1;
                       if(unvisited.count(wd))  {
                           next.push_back(wd);
                           unvisited.erase(wd);
                       }
                   }
                   wd[i] = c; //revert back
               }
           }
           current.swap(next);
           next.clear();
           level++;
       }
       return 0;        
    }
};

/*
=== Solution 3 ===
Bi-directional BFS to reduce search space. Start from two ends (begin/end), and only do BFS from the side with smaller search space. 
When we find one string in the search front that belongs to the front of the other side, we have "connected" the two sides.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
       unordered_set<string> beginSet, nextSet, endSet;
       unordered_set<string> unvisited = wordList;
       int wl = beginWord.size();

       unvisited.erase(beginWord);
       unvisited.erase(endWord);

       beginSet.insert(beginWord);
       endSet.insert(endWord);
       int level = 2;

       while(!beginSet.empty()) {
           //for(unordered_set<string>::iterator it = beginSet.begin(); it != beginSet.end(); ++it) {
           for(auto wd : beginSet) {
               for(int i = 0; i < wl; ++i) {
                   char c = wd[i];
                   for(char ch = 'a'; ch <= 'z'; ++ch) {
                       if(ch == c) continue;
                       wd[i] = ch;
                      if(endSet.count(wd)) return level;
                       if(unvisited.count(wd))  {
                           nextSet.insert(wd);
                           unvisited.erase(wd);
                       }
                   }
                   wd[i] = c; //revert back
               }
           }
           beginSet.swap(nextSet);
           nextSet.clear();
           level++;
           if(beginSet.size() > endSet.size()) beginSet.swap(endSet);
       }
       return 0;
    }
};

/*
=== Solution 4 ===
Bidirectional BFS, recursive solution (64ms!)
*/
class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        unordered_set<string> unvisited = wordList;
        unvisited.erase(beginWord);
        unvisited.erase(endWord);
        unordered_set<string> forwardSet, backwardSet;
        forwardSet.insert(beginWord);
        backwardSet.insert(endWord);
        return ladderLengthUtil(forwardSet, backwardSet, unvisited, 2);
    }
    int ladderLengthUtil(unordered_set<string>& forwardSet, unordered_set<string>& backwardSet, unordered_set<string>& unvisited, int level) {
        if(forwardSet.empty()) return 0;
        if(forwardSet.size() > backwardSet.size()) return ladderLengthUtil(backwardSet, forwardSet, unvisited, level);
        unordered_set<string> next;
        for(auto word : forwardSet) {
            //try all posssibilities
            for(auto it = word.begin(); it != word.end(); ++it) {
                char tmp = *it;
                for(*it = 'a'; *it != 'z'; ++(*it)) {
                    if(*it == tmp) continue;
                    if(backwardSet.count(word)) return level;
                    else if(unvisited.count(word)) { //not visited
                        unvisited.erase(word);
                        next.insert(word);
                    }
                }
                *it = tmp; //revert back
            }
        }
        return ladderLengthUtil(next, backwardSet, unvisited, level+1);
    }
};


/**************************************************** 
 ***    122,Medium,Best Time to Buy and Sell Stock II 
 ****************************************************/

/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

/// Allow infinte transitions. Very simple. Just add up all positive differences!

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max_profit = 0;
        for (int i = 1; i < prices.size(); ++i) {
            int diff = prices[i] - prices[i-1];
            if (diff > 0) max_profit += diff;
        }
        return max_profit;
    }
};

/**************************************************** 
 ***    121,Medium,Best Time to Buy and Sell Stock 
 ****************************************************/

/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
*/

/// Greedy one pass O(n) solution:

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int max_so_far = 0, max_all = 0;
        for(int i = 1; i < n; ++i) {
            int change = prices[i] - prices[i-1];
            if(max_so_far <= 0) max_so_far = change;
            else max_so_far += change;
            max_so_far = max(0, max_so_far);
            max_all = max(max_so_far, max_all);
        }
        return max_all;
    }
};

/**************************************************** 
 ***    116,Medium,Populating Next Right Pointers in Each Node 
 ****************************************************/

/*
Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

    You may only use constant extra space.
    You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

For example,
Given the following perfect binary tree,

         1
       /  \
      2    3
     / \  / \
    4  5  6  7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
*/

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */

// General solution that works for all kinds of trees
// Use a dummy head in current layer.
// Use last layer to help progress the current layer

// Solution 1. Use two dummy heads. Progress layer by layer. Use last layer to help traverse current layer. Remember to set the tail's next to NULL when finishing one layer.

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        //two dummy heads
        TreeLinkNode* phead = new TreeLinkNode(0);
        TreeLinkNode* qhead = new TreeLinkNode(0);
        TreeLinkNode *p = phead, *q = qhead;
        phead->next = root; root->next = NULL;
        while(phead->next) {
            p = p->next;
            while(p && !p->left && !p->right)  p = p->next;
            if(!p) {
                q->next = NULL; //set tail pointer
                phead->next = qhead->next;
                p = phead;
                q = qhead;
                continue;
            }
            if(p->left) {
                q->next = p->left;
                q = q->next;
            }
            if(p->right) {
                q->next = p->right;
                q = q->next;
            }
        }
        delete phead, qhead;
    }
};

// Solution 2. An old solution with the same idea.

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        TreeLinkNode dum1(0), *head(&dum1); //dummy head
        TreeLinkNode *last(root), *curr(NULL); //head of last row, and curr tail node
        while(last) {
            curr = head;
            while(last) {
                if(!last->left && !last->right) {
                    last = last->next;
                    continue;
                }
                curr->next = (last->left ? last->left : last->right);
                curr = curr->next;
                if(curr == last->left && last->right) {
                    curr->next = last->right;
                    curr = curr->next;
                }
                last = last->next;
            }
            last = head->next; //move to new row
            head->next = NULL; //reset to NULL!
        }
    }
};

/**************************************************** 
 ***    113,Medium,Path Sum II 
 ****************************************************/

/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1

return

[
   [5,4,11,2],
   [5,8,4,5]
]
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// DFS backtracking. Recursive solution.
// Caveats: when reaching leaf, compare sum with x, not with zero!

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int> > result;
        if(!root) return result;
        vector<int> path;
        dfs(root, sum, path, result);
        return result;
    }
    void dfs(TreeNode* root, int sum, vector<int>& path, vector<vector<int> >& result) {
        int x = root->val;
        path.push_back(x);
        //reaching leaf
        if(!root->left && !root->right && sum == x) result.push_back(path);
        if(root->left) dfs(root->left, sum-x, path, result);
        if(root->right) dfs(root->right, sum-x, path, result);
        path.pop_back();
    }
};

/**************************************************** 
 ***    109,Medium,Convert Sorted List to Binary Search Tree 
 ****************************************************/

/*
Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution. First find middle element, then use that element as root of tree node, recursively build tree for the list segments before and after middle element, and attach as left and right child of root.

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return helper(head, NULL);
    }
    //construct from head (inclusive) to tail (exclusive)
    TreeNode *helper(ListNode* head, ListNode *tail) {
        if(head == tail) return NULL;
        ListNode *slow = head, *fast = head;
        while(fast->next != tail && fast->next->next != tail) { //this approach returns middle of element, or the first among the two middle ones.
            slow = slow->next;
            fast = fast->next->next;
        }
        //make slow the root
        TreeNode *root = new TreeNode(slow->val);
        root->left = helper(head, slow);
        root->right = helper(slow->next, tail);
        return root;
    }
};


/**************************************************** 
 ***    108,Medium,Convert Sorted Array to Binary Search Tree 
 ****************************************************/

/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.empty()) return NULL;
        int n = nums.size();
        return convert(nums, 0, n-1);
    }
    
    TreeNode* convert(vector<int>& nums, int lo, int hi) {
        if(lo > hi) return NULL;
        int mid = (lo+hi)/2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = convert(nums, lo, mid-1);
        root->right = convert(nums, mid+1, hi);
        return root;
    }
};

// A variant. Range is [beg, end)

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size());
    }

    TreeNode* helper(vector<int>& nums, int beg, int end) {
        if(beg >= end) return NULL;
        int mid = (beg+end)/2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = helper(nums, beg, mid);
        root->right = helper(nums, mid+1, end);
        return root;
    }
};


/**************************************************** 
 ***    103,Medium,Binary Tree Zigzag Level Order Traversal 
 ****************************************************/

/*
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:

[
  [3],
  [9,20],
  [15,7]
]
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Be careful when using bit operator!! if(level & 1 == 0) is wrong!, 1 == 0 has higher priority, should use if (!(level&1)).

/// Using two stacks. Swap the two when exhausting one level. Use a level tag to track polarity, which determines whether left or right subtree gets pushed to stack first
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > ret;
        if(!root) return ret;
        deque<TreeNode*> current, next;
        int level = 0;
        current.push_back(root);
        ret.push_back(vector<int>());
        while(!current.empty() || !next.empty()) { //break when both current and next are empty
            if(current.empty()) { // when exhausing current level ...
                current.swap(next); //swap current and next
                ret.push_back(vector<int>());
                level ++;
            }
            TreeNode *node = current.back();  current.pop_back();
            if(level % 2 == 0) {
                if(node->left) next.push_back(node->left);
                if(node->right) next.push_back(node->right);
            } else {
                if(node->right) next.push_back(node->right);
                if(node->left) next.push_back(node->left);
            }
            ret[level].push_back(node->val);
        }
        return ret;
    }
};

// Solution with 2 stacks, and two loops
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        //stack for two levels
        vector<TreeNode*> current, next;
        int level = 0; //level and parity
        current.push_back(root);
        while(!current.empty()) {
            result.push_back(vector<int>()); //new level
            //user current as stack
            for(vector<TreeNode*>::reverse_iterator it = current.rbegin(); it != current.rend(); ++it) {
                TreeNode *node = *it;
                if(level % 2 == 0) { //l=>r
                    if(node->left) next.push_back(node->left);
                    if(node->right) next.push_back(node->right);
                } else {
                    if(node->right) next.push_back(node->right);
                    if(node->left) next.push_back(node->left);
                }
                //insert to result
                result[level].push_back(node->val);
            }
            current.swap(next);
            next.clear();
            level++;
        }
        return result;
    }
};

// An old solution using struct instead of pair
/// Using a queue, after constructed, reverse odd level elements's order

class Solution {
public:
    struct Element {
        TreeNode *node;
        int level;
        Element(TreeNode *n, int l) : node(n), level(l) {}
    };
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > ret;
        if(!root) return ret;
        deque<Element> q; //queue
        q.push_back(Element(root, 0));
        while(!q.empty()) {
            TreeNode *node = q.front().node;
            int level = q.front().level;
            q.pop_front();
            if(level == ret.size()) ret.push_back(vector<int>());
            ret[level].push_back(node->val);
            if(node->left) q.push_back(Element(node->left, level+1));
            if(node->right) q.push_back(Element(node->right, level+1));
        }
        for(size_t i = 1; i < ret.size(); i += 2) {
            reverse(ret[i].begin(), ret[i].end());
        }
        return ret;
    }
};

/**************************************************** 
 ***    098,Medium,Validate Binary Search Tree 
 ****************************************************/

/*
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than the node's key.
    Both the left and right subtrees must also be binary search trees.

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution.
// store lower and upper bounds of each subtree, initially it is (-inf, inf)
// One corner case is when INT_MIN and INT_MAX is part of the value, so use LONG_MIN and LONG_MAX instead.

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return validate(root, LONG_MIN, LONG_MAX);
    }
    //make sure all tree values between (lo, hi)
    bool validate(TreeNode* root, long lo, long hi) {
        if(!root) return true;
        int x = root->val;
        if(x <= lo || x >= hi) return false;
        return validate(root->left, lo, x) && validate(root->right, x, hi);
    }
};

/**************************************************** 
 ***    096,Medium,Unique Binary Search Trees 
 ****************************************************/

/*
Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

*/

// Dynamic programming. The ways of forming tree of size n can be found by choosing each of the n elements as root, which divides the others as left and right subtrees.

class Solution {
public:
    int numTrees(int n) {
        if(n < 0) return 0;
        if(n == 0 || n == 1) return 1;
        vector<int> count(n+1, 0); //store counts from i=0 to n
        count[0] = count[1] = 1;
        //calculate number of unique trees of size i
        for(int i = 2; i <= n; ++i) {
            //pick k-th number as root, then k elements as left-tree, i-k-1 elements as right-tree
            for(int k = 0; k < i; ++k) {
                count[i] += count[k]*count[i-k-1];
            }
        }
        return count[n];
    }
};


/**************************************************** 
 ***    095,Medium,Unique Binary Search Trees II 
 ****************************************************/

/*
Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Dynamic programming using a 2D array. The trick is to generate the right subtree by using a createNew function with a delta value.

class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n < 0) return vector<TreeNode*>();
        if(n == 0) return vector<TreeNode*>();
        vector<vector<TreeNode*> > dp(n+1); //dp[i]: solutions for tree of size i
        dp[0].push_back(NULL);
        for(int i = 1; i <= n; ++i) { //check tree of size i
            for(int k = 1; k <= i; ++k) { //make k as root
                for(auto l : dp[k-1]) { //construct left subtree
                    for(auto r : dp[i-k]) { //construct right subtree
                        TreeNode *root = new TreeNode(k);
                        root->left = l;
                        root->right = createNew(r, k);
                        dp[i].push_back(root);
                    }
                }
            }
        }
        return dp[n];
    }
    TreeNode* createNew(TreeNode* root, int delta) {
        if(!root) return NULL;
        TreeNode* nr = new TreeNode(root->val+delta); //new root
        nr->left = createNew(root->left, delta);
        nr->right = createNew(root->right, delta);
        return nr;
    }
};


/**************************************************** 
 ***    094,Medium,Binary Tree Inorder Traversal 
 ****************************************************/

/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution (easy).

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        inorder(root, ret);
        return ret;
    }
    void inorder(TreeNode* root, vector<int>& ret) {
        if(!root) return;
        if(root->left) inorder(root->left, ret);
        ret.push_back(root->val);
        if(root->right) inorder(root->right, ret);
    }
};

// Iterative solution using a stack (and a tag indicating the number of times an element appears in stack).
// Slightly different version with modified control flow with tag.

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<pair<TreeNode*, int> > st; //stack
        st.push_back(make_pair(root, 0));
        while(!st.empty()) {
            TreeNode *node = st.back().first;
            int tag = ++st.back().second;
            if(tag == 1) {
                if(node->left) st.push_back(make_pair(node->left, 0));
            } else {
                result.push_back(node->val);
                st.pop_back();
                if(node->right) st.push_back(make_pair(node->right, 0));
            }
        }
        return result;
    }
};

// Another iterative solution by pushing left spline in the stack
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<TreeNode*> st; //stack
        while(root) {
            st.push_back(root);
            root = root->left;
        }
        while(!st.empty()) {
            TreeNode* node = st.back(); st.pop_back();
            result.push_back(node->val);
            node = node->right;
            while(node) {
                st.push_back(node);
                node = node->left;
            }
        }
        return result;
    }
};

// Morris traversal O(n) without using a stack or recursive calls.
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        TreeNode *node = root;
        while(node) {
            if(!node->left) {
                result.push_back(node->val);
                node = node->right;
            } else {
                TreeNode *child = node->left;
                while(child->right != NULL && child->right != node) child = child->right;
                if(child->right == NULL) {
                    child->right = node; // first time, modify right pointer
                    node = node->left; //move to left child
                } else {
                    child->right = NULL; //second time, reset right pointer to NULL
                    result.push_back(node->val);
                    node = node->right;
                }
            }
        }
        return result;
    }
};

// Morris traversal with a slightly different while loop (visit node in the end of loop body)
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        TreeNode *node = root;
        while(node) {
            if(node->left) {  // has left subtree
                TreeNode *child = node->left;
                while(child->right != NULL && child->right != node) child = child->right;
                //reached right most child of left subtree
                if(child->right == NULL) { //first time
                    child->right = node;
                    node = node->left;
                    continue;
                } else { //second time
                   child->right = NULL; //second time
                }
            }
            //visit node
            result.push_back(node->val);
            node = node->right;
        }
        return result;
    }
};



/**************************************************** 
 ***    093,Medium,Restore IP Addresses 
 ****************************************************/

/*
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter) 
*/

// Recursive solution #1.
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        if(s.empty()) return result;
        string tmp;
        dfs(s, 0, 0, tmp, result);
        return result;
    }
    void dfs(const string& s, int i, int count, string tmp, vector<string>& result) {
        int n = s.size();
        if(i == n && count == 4) {
            result.push_back(tmp);
            return;
        }
        if(i == n || count == 4) return;
        if(i != 0) tmp += '.';
        if(s[i] == '0') {
            dfs(s, i+1, count+1, tmp+'0', result);
            return;
        }
        for(int k = i, val = 0; k < n; k++) {
            val = val*10 + (s[k] - '0');
            if(val >= 256) break;
            tmp += s[k];
            dfs(s, k+1, count+1, tmp, result);
        }
   }
};

// Recursive solution #2. 
// Need to add 4 periods, last one has to be after last character.
// store positions of periods (index of character right before newly added period), and reconstruct the string when valid solutions are found
// Caveat: string::insert function argument is the index which the new character is inserted before.
// Another caveat: ip address segments cannot have leading zeros, except .0. case, others like .03. or .00. are illegal. Need to filter them out

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ret;
        vector<int> dotPos(4, -1); //dot positions in the s
        restore(s, 0, 0, dotPos, ret);
        return ret;
    }
    //checking substring starting at s[i] for dot number k (0-3), add values to dotPos
    void restore(const string& s, int i, int k, vector<int>& dotPos, vector<string>& ret) {
       if (k == 4) { //already placing 4 dots (one at the end)
          //onlyd add when i reaches the end
          if (i == s.size()) ret.push_back(construct(s, dotPos));
          return;
       }
       if (i == s.size()) return;
       int v = 0;
       for (int j = i; j < s.size(); ++j) {
          v = 10*v + s[j] - '0';
          if(v >= 256) break;
          dotPos[k] = j; //dot is after j's position
          restore(s, j+1, k+1, dotPos, ret);
          if(s[i] == '0') break; //if leading character is '0', do not continue loop ('.00.' is illegal IP segment)
       }
    }
    string construct(const string& s, const vector<int>& dotPos) {
        string ret = s;
        ret.insert(dotPos[2]+1, 1, '.');
        ret.insert(dotPos[1]+1, 1, '.');
        ret.insert(dotPos[0]+1, 1, '.');
        return ret;
    }

};


/**************************************************** 
 ***    090,Medium,Subsets II 
 ****************************************************/

/*
Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/

// Solution 1. Similar to #78, DFS backtracking with fan-out = 2.
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        if(i == nums.size()) {
            result.push_back(tmp);
            return;
        }
        int j = i;
        while(j < nums.size() && nums[j] == nums[i]) j++;
        //j is index of first element != nums[i], or end
        //not adding nums[i] to set
        dfs(nums, j, tmp, result);
        //adding 1 to j-i nums[i] to set
        for(int k = 0; k < j-i; ++k) {
            tmp.push_back(nums[i]);
            dfs(nums, j, tmp, result);
        }
        //revert back
        for(int k = 0; k < j-i; ++k) {
            tmp.pop_back();
        }
    }
};

// Solution 2. Similar to #78, DFS backtracking with fan-out = number of unused elements
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        vector<int> tmp;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        result.push_back(tmp);
        for(int j = i; j < nums.size(); ++j) {
            if(j == i || nums[j] != nums[j-1]) { //ignore duplicates
                tmp.push_back(nums[j]);
                dfs(nums, j+1, tmp, result);
                tmp.pop_back();
            }
        }
    }
};

// Solution 3. Similar to #78, dynamic programming.
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        result.push_back(vector<int>()); //empty set
        int i = 0;
        int n = nums.size();
        while(i < n) {
            int j = i;
            while(j < n && nums[j] == nums[i]) j++;
            int ndup = j-i; //number of duplicates
            //add 1 - ndup nums[i] to existing solution
            int size = result.size();
            for(int k = 0; k < ndup; ++k) {
                for(int l = k*size; l < (k+1)*size; ++l) {
                    result.push_back(result[l]);
                    result.back().push_back(nums[i]);
                }
            }
            i = j;
        }
        return result;
    }
};


/**************************************************** 
 ***    082,Medium,Remove Duplicates from Sorted List II 
 ****************************************************/

/*
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// use two pointers. Also dummy head, because head might be deleted.

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;

        ListNode *p = dummy, *q = p->next;
        //p is tail of processed list, q is its next, r is one node past the last duplicated entry.
        while(q) {
            ListNode* r = q->next;
            while(r && r->val == q->val) r = r->next;
            //r is either null or first entry not equal to q
            if(r == q->next) { //no duplicated entry
                p = q;
                q = r; //just move forward
                continue;
            }
            //then delete everything from q to r's ancestor
            while(q != r) {
                ListNode * t = q;
                delete t;
                q = q->next;
            }
            //after loop q == r
            p->next = q;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

/**************************************************** 
 ***    081,Medium,Search in Rotated Sorted Array II 
 ****************************************************/

/*
Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/

/*
Binary search. The array can be broken into two part, first part is 4-7, second part is 0-2. If array is unrotated, then only first part exists (corner case). 
There are three anchor points, lo, hi, and mid.
First determine whether mid is in first half or second half. Due to duplicated items, we now has three cases:
1. Mid is in first half iff nums[mid] > nums[lo] 
2. Mid is in second half iff nums[mid] < nums[lo]
3. if nums[mid] == nums[lo], we can't say for sure which part mid belongs to, but we know that nums[lo] is not target, so we simply increment lo. 
Examples for 3. 
 2 2 2 2 3 2 2
lo    mid   hi  (mid is in first half)
 2 2 3 2 2 2 2
lo    mid   hi  (mid is in second half)

1. If mid is in first half, we know that nums[mid] >= nums[lo] (could be equal because mid can be lo, when hi = lo+1), if target falls between the two, then the index has to be between lo and mid. Otherwise, it is between mid and hi.
2. If mid is in second half, we know that nums[mid] <= nums[hi] (could be equal because mid can be hi, when hi = lo), if target falls between the two, then the index has to be between mid and hi. Otherwise, it is between lo and mid.
*/

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int lo(0), hi(n-1);
        while(lo <= hi) {
            int mid = lo + (hi-lo) / 2;
            if(target == nums[mid]) return true;
            if (nums[mid] > nums[lo]) {
                if(target >= nums[lo] && target < nums[mid]) hi = mid -1;
                else lo = mid + 1;
            } else if (nums[mid] < nums[lo]) {
                if(target <= nums[hi] && target > nums[mid]) lo = mid + 1;
                else hi = mid - 1;
            } else {
                lo++;
            }
        }
        return false;
    }
};

/**************************************************** 
 ***    080,Medium,Remove Duplicates from Sorted Array II 
 ****************************************************/

/*
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length. 
*/

// Solution: two pointers. 
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return n;
        int len = 0;
        int i = 0, j = 0;
        while(i < n) {
            j = i+1;
            while(j < n && nums[j] == nums[i]) j++;
            if(j >= i+1) nums[len++] = nums[i];
            if(j > i+1) nums[len++] = nums[i];
            i = j;
        }
        return len;
    }
};

// A old solution
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if(n == 0) return 0;
   		int i(0), j(1), prev = INT_MAX, count = 0;
		for(j = 0; j < n; ++j) {
		    if(A[j] == prev) count++;
		    else count = 1;
		    prev = A[j];
		    if(count <= 2) A[i++] = A[j]; 
		}
		return i;   
    }
};

/**************************************************** 
 ***    079,Medium,Word Search 
 ****************************************************/

/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/

/* 
Recursive solution using DFS
Several optimizations:
1. Do not use another array to store the visited status of the board. Instead, set the visited board character as '*', and set it back to original at retrace stage.
2. For checking validity of new positions, leave it to the recursive function (if not legal simply return false). If do something like this, will lead to TLE.

        if(i > 0 && board[i-1][j] != '*' && existHelper(board, i-1, j, word, k+1)) return true;
        if(i < m-1 && board[i+1][j] != '*' && existHelper(board, i+1, j, word, k+1)) return true;
        if(j > 0 && board[i][j-1] != '*' && existHelper(board, i, j-1, word, k+1)) return true;
        if(j < n-1 && board[i][j+1] != '*' && existHelper(board, i, j+1, word, k+1)) return true;

*/

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty() || board[0].empty()) return false;
        if(word.empty()) return true;
        int m = board.size(), n = board[0].size();
        if(m*n < word.size()) return false;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(existHelper(board, i, j, word, 0)) return true;
            }
        }
        return false;
    }
    bool existHelper(vector<vector<char> >& board, int i, int j, const string& word, int k) {
        if(k == word.size()) return true; //found
        int m = board.size(), n = board[0].size();
        if(i < 0 || i >= m || j < 0 || j >= n) return false; //not legal position
        if(board[i][j] == '*') return false; //already visited
        if(board[i][j] != word[k]) return false; //not match
        char c = board[i][j];
        board[i][j] = '*';
        //matches, move to next one
        if(existHelper(board, i-1, j, word, k+1)) return true;
        if(existHelper(board, i+1, j, word, k+1)) return true;
        if(existHelper(board, i, j-1, word, k+1)) return true;
        if(existHelper(board, i, j+1, word, k+1)) return true;
        
        board[i][j] = c; //retrace
        return false;
    }
};

// An old iterative solution
class Solution {
public:
	//move from current position (row,col) to next position
	void move(int &row, int &col, int dir) {
		if(dir == 1) col += 1; //right
		else if(dir == 2) row -= 1; //up
		else if(dir == 3) col -= 1; //left
		else if(dir == 4) row += 1; //down
		else row = col = -1; //not move
	}
	//check if position (row, col) exceeds boundary
	bool isValid(int row, int col, int m, int n) {
		return(row >= 0 && row < m && col >= 0 && col < n);
	}
	bool exist(vector<vector<char> > &board, string word) {
		int m = board.size();
		int n = board[0].size();
		int tot = m*n;
		int len = word.size();
		int k = 0; //k-th character in word
		vector<int> dir(len, 1);  //directions at step k
		vector<int> row(len, -1); //row number at step k
		vector<int> col(len, -1); //column number at step k
		vector<vector<bool> > visited(m, vector<bool>(n, false));//site visited? 
		
		for(int l = 0; l < tot; ++l) { //loop thru all elements in the board
			//invariant: k characters matched (now matching word[k] with position[k] determined from position[k-1] and dir[k-1])
			k = 0; //reset k everytime!
			while(1) {
			    if(k == len) return true; //already found!
			    if(k > 0 && dir[k-1] > 4) { //tried all directions, retrace
			    	dir[k-1] = 1; //reset to first direction
			    	visited[row[k-1]][col[k-1]] = false; //reset
				    row[k-1] = col[k-1] = -1;
				    k--;
				    if(k == 0) break; //breaking condition
				    dir[k-1] ++; //last one should increment
				    continue;
				}
			    //find next position
			    int nextRow = row[k-1], nextCol = col[k-1];
			    if(k == 0) { nextRow = l/n; nextCol = l%n; }
			    else move(nextRow, nextCol, dir[k-1]);
			    
			    //check match?
			    if(k == 0) { //first character special case
				    if(board[nextRow][nextCol] != word[k]) break; 
				    else { //matched first character
				        row[k] = nextRow; col[k] = nextCol;
				        visited[row[k]][col[k]] = true;
				        k++; //try next one
				    }
				} else if(!isValid(nextRow, nextCol, m, n) || board[nextRow][nextCol] != word[k] || visited[nextRow][nextCol]) { //no match
    				dir[k-1] ++;
				} else { //found match
		    	    row[k] = nextRow; col[k] = nextCol;
			        visited[row[k]][col[k]] = true; //update visited
			        k++;
				}
			}
		}
		return false;
	}
};



/**************************************************** 
 ***    078,Medium,Subsets 
 ****************************************************/

/*
Given a set of distinct integers, nums, return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/

// Solution 1. Recursive backtracking using DFS. Fan-out is 2 (for each number, add or not add).

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        if(i == nums.size()) {
            result.push_back(tmp);
            return;
        }
        // not taking nums[i]
        dfs(nums, i+1, tmp, result);
        // taking nums[i]
        tmp.push_back(nums[i]);
        dfs(nums, i+1, tmp, result);
        tmp.pop_back(); //revert
    }
};

// Solution 2. Recursive backtracking using DFS. Fan-out is number of unused elements, less tree depth and thus better efficiency than 1.

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > result;
        vector<int> tmp;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        result.push_back(tmp);
        for(int j = i; j < nums.size(); ++j) { //choose one from unused numbers
            tmp.push_back(nums[j]);
            dfs(nums, j+1, tmp, result);
            tmp.pop_back();
        }
    }
};

// Solution 3. Dynamic programming. For each number, add to previous solution.
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        result.push_back(vector<int>()); //empty set
        for(int i = 0; i < nums.size(); ++i) {
            //add nums[i] to all previous solutions
            int size = result.size();
            for(int j = 0; j < size; ++j) {
                result.push_back(result[j]);
                result.back().push_back(nums[i]);
            }
        }
        return result;
    }
};

// Solution 4. Use bit operation. There are pow(2, n) results, we can label them in a consistent order similar to Solution 3.
// for example [1,2,3]:
// subset:       [], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]
// id(base 10):  0    1    2      3     4     5       6         7
// id(base 2):  000  001  010    011   100   101     110       111
// As we can see, number 1 (the 0-th number) only appears when last digit is set. number 2 (the 1st number) only appears when second from last digit is set, and so on. Thus, for each id, we can check which digit are set, and add the corresponding number to the subset.
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int size = 1 << n;
        sort(nums.begin(), nums.end());
        vector<vector<int> > result(size, vector<int>());
        for(int i = 0; i < result.size(); ++i) {
            for(int j = 0; j < n; ++j) {
                if(i & (1 << j)) result[i].push_back(nums[j]);
            }
        }
        return result;
    }
};


/**************************************************** 
 ***    077,Medium,Combinations 
 ****************************************************/

/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/

// Solution 1. Recursive solution. Start with k trials, every time decrement trials. Stop recursion when there is no trials left (k == 0). (12ms)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        dfs(1, n, k, tmp, result);
        return result;
    }
    //k trials left, start from number i, maximum is n
    void dfs(int i, int n, int k, vector<int>& tmp, vector<vector<int> >& result) {
        if(k == 0) {
            result.push_back(tmp);
            return;
        }
        if(i > n) return; //no numbers available
        int size = tmp.size();
        for(int j = i; j <= n; ++j) { //choose number between i and n
            tmp[size-k] = j; //choose number j
            dfs(j+1, n, k-1, tmp, result); //dfs starting with j+1
        }
    }
};

// Solution 2. Optimized recursive solution. Stop recursion after making the decision for the last trial (k == 1), also avoid uncessary trial when i > n.
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        dfs(1, n, k, tmp, result);
        return result;
    }
    //k trials left, start from number i, maximum is n
    void dfs(int i, int n, int k, vector<int>& tmp, vector<vector<int> >& result) {
        int size = tmp.size();
        for(int j = i; j <= n; ++j) { //choose number between i and n
            tmp[size-k] = j; //choose number j
            if(k == 1) result.push_back(tmp); //reaching the end
            else if(j < n) dfs(j+1, n, k-1, tmp, result); //dfs starting with j+1
        }
    }
};	

// Solution 3. Iterative. Save results at i == k. (16ms)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        int i = 0; 
        while(i >= 0) { //the i-th choice ( 0 <= i < k)
            if(i == k) { 
                result.push_back(tmp); 
                i--; //backtrace!
                continue; 
            }
            tmp[i]++; //choose the next number
            if(tmp[i] > n) { i--; continue; } //back trace
            i++; //go to next step
            if(i < k) tmp[i] = tmp[i-1]; //choose right starting point for the next tmp[i]++
        }
        return result;
    }
};

// Solution 3. Iterative, optmized and simpler. Save results at i == k-1. (8ms)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        int i = 0; 
        while(i >= 0) { //the i-th choice ( 0 <= i < k)
            tmp[i]++; //choose the next number
            if(tmp[i] > n) i--; //back trace
            else if (i == k-1) result.push_back(tmp);
            else {
                i++; //go to next step
                tmp[i] = tmp[i-1]; //choose right starting point for the next tmp[i]++
            }
        }
        return result;
    }
};


/**************************************************** 
 ***    060,Medium,Permutation Sequence 
 ****************************************************/

/*
The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

    "123"
    "132"
    "213"
    "231"
    "312"
    "321"

Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.
*/

/* Solution using modular relation to determine the most significant digit and moving downward. This solution does not print the numbers in lexigraphical order.
 Maintain an array storing whether a particular digit has been used or not (e.g. used[2] denotes char '3'). Use a helper function to find the K-th unused character.
 k-- to make k start from 0
 e.g. n = 4
 1... (3!)  k = 0 - 5 (k / 3! = 0)
 2... (3!)  k = 6 - 11 (k / 3! = 1)
 3... (3!)  k = 12 - 17 (k / 3! = 2)
 4... (3!)  k = 18 - 23 (k / 3! = 3)
Caveats: the next permutation algorithm does not pass here due to TLE: has to move forward one step at a time!
*/

class Solution {
public:
    string getPermutation(int n, int k) {
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        k = (k-1) % fact;
        vector<int> used(n, false);
        string result(n, '0');
        for(int i = 0; i < n; ++i) { //from MSD to LSD
            fact = fact / (n-i);
            int j = k / fact;
            int idx = findUnused(used, j);
            used[idx] = true;
            result[i] = idx + '1';
            k %= fact;
        }
        return result;
    }

    int findUnused(const vector<int>& used, int i) {
        for(int j = 0; j < used.size(); ++j) {
            if(!used[j]) {
                if(i-- == 0) return j;
            }
        }
        return -1;
    }
};

/*
Solution 2 using a bit status number.
Caveat:
 When testring if a digit is unset, use
 !(x & (1 << n)). not ~ , because inverting boolean and inverting bit number are totally different things!
 ! 1 = !(true) = false
 ~ 1 = -2 = true!
*/

class Solution {
public:
    string getPermutation(int n, int k) {
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        k = (k-1) % fact;
        int state = 0; //used state: digit i means whether k+1 has been used
        string result(n, '0');
        for(int i = 0; i < n; ++i) { //from MSD to LSD
            fact = fact / (n-i);
            int j = k / fact;
            int idx = findUnused(state, j);
            state |= (1 << idx);
            result[i] = idx + '1';
            k %= fact;
        }
        return result;
    }

    int findUnused(int state, int i) {
        for(int j = 0; j < 32; ++j) {
            if(!(state & (1 << j))) {
                if(i-- == 0) return j;
            }
        }
        return 32;
    }
};

// Solution 3 using a string storing unused characters, when a character is used, remove the character
// Notice the usage of two STL functions: iota and string::erase

class Solution {
public:
    string getPermutation(int n, int k) {
        string dict(n, '0');
        iota(dict.begin(), dict.end(), '1'); // dict = '1234...n'
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        k = (k-1) % fact;
        string result(n, '0');
        for(int i = 0; i < n; ++i) { //from MSD to LSD
            fact = fact / (n-i);
            int j = k / fact;
            result[i] = dict[j];
            dict.erase(j, 1); //erase j-th character
            k %= fact;
        }
        return result;
    }
};



/**************************************************** 
 ***    055,Medium,Jump Game 
 ****************************************************/

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false. 
*/

/* Solution 1. Maintain a variable (step) for the maximum steps at each position. Scan forward, say the maximum step at position i is step, then we move one step further, the maximum step can be either step-1 (because we moved one step forward), or the maximum step at i+1. Thus
step = max(step-1, nums[i]);
If step = 0, then cannot jump.
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        if(nums[0] == 0) return false;
        int step = nums[0];
        for(int i = 1; i < n-1; ++i) {
            step = max(step-1, nums[i]);
            if(step <= 0) return false;
        }
        return true;
    }
};

/*
Solution 2. Similar to Solution 1, but Keep a variable (rightEnd) for the maximum reachable index at each position. Scan forward, if the current position is beyond the rightEnd, then cannot jump. If rightEnd exceeds n-1, then can jump.
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        int rightEnd = 0, i = 0;
        for(int i = 0; i <= rightEnd; i++) {
            rightEnd = max(rightEnd, i + nums[i]);
            if(rightEnd >= n-1) return true;
        }
        return false;
    }
};

/*
Solution 3. Standard BFS, each step, maintain a range [lo, hi] reachable from beginning, then scan all elements in the range, and calculate the newly reachable range as [hi+1, max( nums[i]+i) for all i between lo and hi]. If hi is not increased in the newly range, then cannot jump.
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        int lo = 0, hi = 0;
        while(hi < n-1) {
           int tmp = hi;
           for(int i = lo; i <= tmp; ++i) {
               hi = max(hi, i+nums[i]);
           }
           if(hi == tmp) return false;
           lo = tmp+1;
        }
        return true;
    }
};

/*
Solution 4. Start from right and scan to left. Find first element reachable to end, and make that element the new end.
e.g. [4 3 4 1 0 2]
search starts from 0, and found 4 reachable to end. Then problem reduces to the [4 3 4] subarray.
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        int i = n-1, j = 0;
        while(i > 0) {
           j = i-1;
           while(j >= 0 && nums[j] < i-j) { //find first element that can reach to nums[i]
              j--;
           }
           if(j == -1) return false; //not found
           i = j;
        }
        return true;
    }
};

/**************************************************** 
 ***    053,Medium,Maximum Subarray 
 ****************************************************/

/*
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

click to show more practice.
More practice:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/

// Solution 1. Divide and conquer.
// Find max from left sub array, right sub array, and crossing arrays.
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        return maxSubArrayAux(nums, 0, nums.size()-1);
    }
    
    int maxSubArrayAux(vector<int>& nums, int lo, int hi) {
        if(lo > hi) return INT_MIN;
        if(lo == hi) return nums[lo]; //only one element
        int mid = lo + (hi - lo) / 2; //break array at mid | mid+1
        int max1 = maxSubArrayAux(nums, lo, mid);
        int max2 = maxSubArrayAux(nums, mid+1, hi);
        int max3 = maxCrossing(nums, lo, hi, mid);
        return max(max(max1, max2), max3);
    }
    
    int maxCrossing(vector<int>& nums, int lo, int hi, int mid) {
        int left_sum = nums[mid], max_left_sum = left_sum;
        int right_sum = nums[mid+1], max_right_sum = right_sum;
        int jleft = mid-1, jright = mid+2;
        while(jleft >= lo) {
            left_sum += nums[jleft];
            max_left_sum = max(max_left_sum, left_sum);
            jleft--;
        }
        while(jright <= hi) {
            right_sum += nums[jright];
            max_right_sum = max(max_right_sum, right_sum);
            jright++;
        }
        return max_left_sum + max_right_sum;
    }
};


/// Solution 2 dynamic programming.
/*
Maximum ending at nums[k] can be obtained from nums[k] and maximum ending at nums[k-1].
1. if max ending at nums[k-1] is positive, then we simply add nums[k] to obtain max ending at nums[k].
2. if max ending at nums[k-1] is negative, then we can discard everything before nums[k], and use nums[k] as max ending at nums[k].
When assigning max_all, using conditional clause (as below) is 4ms faster than using std::max.
*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        int max_ending_here = 0, max_all = INT_MIN;
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            max_ending_here = max_ending_here > 0 ? (max_ending_here + nums[i]) : nums[i];
            if(max_all < max_ending_here) max_all = max_ending_here;
        }
        return max_all;
    }
};

/**************************************************** 
 ***    049,Medium,Group Anagrams 
 ****************************************************/

/*
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:

    For the return value, each inner list's elements must follow the lexicographic order.
    All inputs will be in lower-case.
*/

// Solution 1. Using a hash table to store the already found anagrams. Use the sorted string as the key. 68ms.
// For each string in strs, if found in table, then insert to approapriate positions, otherwise, add a new vector to the result, and push the string to that vector.
// Finally, sort each sub-vector

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if(strs.empty()) return result;
        unordered_map<string, int> dict;

        for(int i = 0; i < strs.size(); ++i) {
            string s = strs[i];
            sort(s.begin(), s.end());
            if(dict.count(s)) { //found anagrams
                result[dict[s]].push_back(strs[i]);
            } else { //new entry
                dict[s] = result.size();
                result.push_back(vector<string>(1, strs[i]));
            }
        }
        for(int i = 0; i < result.size(); ++i) {
            sort(result[i].begin(), result[i].end());
        }
        return result;
    }
};

// Solution 2. 400ms. Not a very efficient solution.
// First sort the strs array by a customized compare function (compare each string's sorted forms). After this step all anagrams are ajacent to each other. Next step scan the array and group anagrams using the isAnagram function. Still need to sort each group in the end.

bool compare(const string& s, const string& t) {
    string ss = s, tt = t;
    sort(ss.begin(), ss.end());
    sort(tt.begin(), tt.end());
    return ss < tt;
}

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if(strs.empty()) return result;
        sort(strs.begin(), strs.end(), compare);

        for(int i = 0; i < strs.size(); ++i) {
            if(i == 0 || !isAnagram(strs[i], strs[i-1]))
                result.push_back(vector<string>());
            result.back().push_back(strs[i]);
        }
        for(int i = 0; i < result.size(); ++i) {
            sort(result[i].begin(), result[i].end());
        }
        return result;
    }
    bool isAnagram(const string& s, const string& t) {
        if(s.size() != t.size()) return false;
        int n = s.size();
        if(n == 0) return true;
        if(n == 1) return s == t;
        vector<int> dict(26, 0);
        for(auto c : s) dict[c-'a']++;
        for(auto c : t) {
            if(--dict[c-'a'] < 0) return false;
        }
        return true;
    }
};

// Solution 3. TLE. Brute force solution, very inefficient.
// One pass. Construct result as we scan strs, for each string, linearly scan all anagram groups in results. Compare the string with the first entry of the anagram group. If found equal, insert to this group. Otherwise, append a new group to end of results and insert the string to this group.

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if(strs.empty()) return result;
        for(auto s : strs) {
            bool hasAnagram = false;
            for(int i = 0; i < result.size(); ++i) {
                if(isAnagram(result[i][0], s)) {
                    result[i].push_back(s);
                    hasAnagram = true;
                    break;
                }
            }
            if(!hasAnagram) result.push_back(vector<string>(1, s));
        }
        for(auto s : result) {
            sort(s.begin(), s.end());
        }
        return result;
    }
    bool isAnagram(const string& s, const string& t) {
        if(s.size() != t.size()) return false;
        int n = s.size();
        if(n == 0) return true;
        if(n == 1) return s == t;
        vector<int> dict(26, 0);
        for(auto c : s) dict[c-'a']++;
        for(auto c : t) {
            if(--dict[c-'a'] < 0) return false;
        }
        return true;
    }
};




/**************************************************** 
 ***    047,Medium,Permutations II 
 ****************************************************/

/*
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1]. 
*/

// Solution 1. Use next permutation algorithm to print permutations in lexigraphical order (see 031)
// Copied from 046_permutation.cc

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end());
        result.push_back(nums);
        while(nextPermutation(nums)) result.push_back(nums);
        return result;
    }
    bool nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = n-2, l = n-1;
        while(k >= 0 && nums[k] >= nums[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) return false;
        while(l > k && nums[l] <= nums[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(nums[k], nums[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(nums[i++], nums[j--]);
        return true;
    }
};

// Solution 2. Recursive solution with swapping adapted from 046_permutations.cc. 
// To deal with duplicated entries, we can't use something simpler such as checking current to be exchanged ia equal to previously exchanged one, because the subarray maybe unsorted, for example, given aabbccd, and after a while we have bcd|caba, and the second part is unsorted. 
// Unless using a set structure, there is no way of preventing 'c' to be swapped with second 'a', because the previous is a 'b'.

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        dfs(nums, 0, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<vector<int> >& result) {
        int n = nums.size();
        if(i == n) {
            result.push_back(nums);
            return;
        }
        unordered_set<int> used;
        for(int k = i; k < n; ++k) {
            if(used.count(nums[k])) continue; //ignore duplicates that are already used
            used.insert(nums[k]); //insert to used table
            swap(nums[i], nums[k]);
            dfs(nums, i+1, result);
            swap(nums[i], nums[k]);
        }
    }
};

// Solution 3. Recursive solution adapted from Solution 3 in 046_permutations.cc. using a bit number representing status. Adapted to duplicated cases. Use a number "last" to store the last number used. When scanning forwards, skip the numbers equal to last as well.

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int state = 0; //bit states for 0 to n-1 
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> tmp(n, 0);
        dfs(nums, 0, tmp, result, state);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result, int state) {
        int n = nums.size();
        if(i == n) {
            result.push_back(tmp);
            return;
        }
        int last = INT_MIN; // assume no numbers are INT_MIN
        for(int k = 0; k < n; ++k) { //try all possible numbers
            if((state & (1 << k)) || nums[k] == last) continue; //already used, or duplicate entries
            last = tmp[i] = nums[k]; //use nums[k]
            state |= (1 << k);
            dfs(nums, i+1, tmp, result, state);
            state &= ~(1 << k); //retrace
        }
    }
};

// Solution 4. An iterative solution. Similar to that of 046_permutations. Only difference is that when we scan forward, if we see a used character OR a character that is the same as previous one, then we continue searching.
// A tricky case is when there is no previous character. So need to carefully write the conditiont in while loop.

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int n = nums.size(), i(0);
        sort(nums.begin(), nums.end()); //first sort array
        vector<bool> used(n, false); //whether i-th number has been used
        vector<int> pos(n, -1); //position in nums for the number chosen for i-th position in permutation sequence
        while(i >= 0) { //check i-th position
            if(i == n) {
                vector<int> tmp(n, 0);
                for(int k = 0; k < n; ++k) tmp[k] = nums[pos[k]];
                result.push_back(tmp);
                i--; //retrace
                continue;
            }
            //find next unused number for i-th selection
            if(pos[i] >= 0) used[pos[i]] = false; //unset
            int tmp_pos = pos[i];
            pos[i]++;
            while(pos[i] < n && (used[pos[i]] || (tmp_pos >= 0 && nums[pos[i]] == nums[tmp_pos]))) pos[i]++;
            if(pos[i] == n) { //no numbers left
                pos[i] = -1;
                i--; //retrace
                continue;
            }
            used[pos[i]] = true;
            //find next pos[i]
            i++;
        }
        return result;
    }
};


/**************************************************** 
 ***    046,Medium,Permutations 
 ****************************************************/

/*
Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1]. 
*/

// Solution 1. Use next permutation algorithm to print permutations in lexigraphical order (see 031)
// use a tag to indicate the status of permutation. If reaching the last permutation (descending order), return false. 
// Also works for cases when duplicated entries exist
// Caveats: 
// 1. If use a counter to print exactly n! permutations, then does not for cases where duplicated entries exist!
// 2. array should be sorted in the beginning!

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end()); //first sort the array!
        result.push_back(nums);
        while(nextPermutation(nums)) result.push_back(nums);
        return result;
    }
    bool nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = n-2, l = n-1;
        while(k >= 0 && nums[k] >= nums[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) return false;
        while(l > k && nums[l] <= nums[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(nums[k], nums[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(nums[i++], nums[j--]);
        return true;
    }
};

// Solution 2. Recursive solution using swapping. Does not work for duplicated cases. Developing a method that deals with duplicated cases are not straightforward, because the array order is destructed during the swapping! One hack is to introduce a table storing used elements, and avoid using them again in the same level of dfs search (see 047)
// Note that this method does not print the permutations in lexigraphical order!

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        dfs(nums, 0, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<vector<int> >& result) { 
        int n = nums.size();
        if(i == n) {
            result.push_back(nums);
            return;
        }
        for(int k = i; k < n; ++k) {
            swap(nums[i], nums[k]);
            dfs(nums, i+1, result);
            swap(nums[i], nums[k]);
        }
    }
};

// Solution 3. Recursive solution, each time take a number, use a bit status number indicating which number has been taken. Can be extended to duplicated cases (see 047).
// Some bit operators:
// checking if k-th number is used: if(state & (1 << k))
// set the tag for the k-th number: state != (1 << k)
// unset the tag for the k-th number: state &= ~(1 << k)

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int state = 0; //bit states for 0 to n-1 
        int n = nums.size();
        vector<int> tmp(n, 0);
        dfs(nums, 0, tmp, result, state);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result, int state) {
        int n = nums.size();
        if(i == n) {
            result.push_back(tmp);
            return;
        }
        for(int k = 0; k < n; ++k) { //try all possible numbers
            if(state & (1 << k)) continue; //already used
            tmp[i] = nums[k]; //use nums[k]
            state |= (1 << k);
            dfs(nums, i+1, tmp, result, state);
            state &= ~(1 << k); //retrace
        }
    }
};

// Solution 4. An iterative solution using O(n) space to track the status of each number, and another O(n) space to record the positions of each number used.

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int n = nums.size(), i(0);
        vector<bool> used(n, false); //whether i-th number has been used
        vector<int> pos(n, -1); //position in nums for the number chosen for i-th position in permutation sequence
        while(i >= 0) { //check i-th position
            if(i == n) {
                vector<int> tmp(n, 0);
                for(int k = 0; k < n; ++k) tmp[k] = nums[pos[k]];
                result.push_back(tmp);
                i--; //retrace
                continue;
            }
            //find next unused number for i-th selection
            if(pos[i] >= 0) used[pos[i]] = false; //unset
            pos[i]++;
            while(pos[i] < n && used[pos[i]]) pos[i]++;
            if(pos[i] == n) { //no numbers left
                pos[i] = -1;
                i--; //retrace
                continue;
            }
            used[pos[i]] = true;
            //find next pos[i]
            i++;
        }
        return result;
    }
};



/**************************************************** 
 ***    043,Medium,Multiply Strings 
 ****************************************************/

/*
Given two numbers represented as strings, return multiplication of the numbers as a string.

Note: The numbers can be arbitrarily large and are non-negative.
*/

/// Just minic the elementary school multiplication method
///      1 2 3 4   (num2, outer loop)
///    x   5 6 7   (num1, inner loop)
/// -------------
///      8 6 3 8
///    7 4 0 4
///  6 1 7 0
/// -------------
///  6 9 9 6 7 8
/// If nums1 and num2 have l1 and l2 digits, without carry over, the product will have l1+l2-1 digits. In this way, product of num1[i] and num2[j] should be aligned to num[i+j].
/// Start from the bottom up. Update the result in-place (instead of creating intermediate strings to store the products)
/// each time inner loop is done, the carry should go to result[i-1] or additional carry digit.

class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        int l1 = num1.size(), l2 = num2.size();
        string result(l1+l2-1, '0'); // result has l1+l2-1 digits
        int sum = 0, carry = 0;
        for(int i = l1-1; i >= 0; --i) {
            carry = 0;
            for(int j = l2-1; j >= 0; --j) {
                sum = (num1[i] - '0')*(num2[j] - '0') + (result[i+j] - '0') + carry;
                carry = sum / 10;
                sum %= 10;
                result[i+j] = sum + '0';
            }
            if(carry > 0) {
                if(i > 0) result[i-1] = carry + '0'; 
                else result = char(carry + '0') + result;
            }
        }
        
        return result;
    }
};

// Another solution, create an intemediate string for products, shift the products to correct positions by appending proper number of zeroes, and add products together. Optimization on the for loops, so that roughly strings of similar lengths are added. But still very slow ...
class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        int l1 = num1.size(), l2 = num2.size();
        string result = "0";
        for(int k = 0; k < l1+l2-1; ++k) {
            for(int i = max(0, k-l2+1); i <= min(k, l1-1); ++i) {
                int j = k-i;
                char c1 = num1[l1-i-1], c2 = num2[l2-j-1];
                string prod = num2str((c1-'0')*(c2-'0'));
                prod.append(k, '0');
                result = add(result, prod);
            }
        }
        return result;
    }
    
    string num2str(int num) {
        if(num == 0) return "0";
        string result;
        while(num) {
            result = char(num % 10 + '0') + result;
            num /= 10;
        }
        return result;
    }

    string add(const string& num1, const string& num2) {
        int l1 = num1.size(), l2 = num2.size();
        int l = max(l1, l2);
        string result(l, '0');
        int sum = 0, carry = 0;
        for(int i = 0; i < l; ++i) {
            if(i >= l1) sum = (num2[l2-i-1] - '0') + carry;
            else if(i >= l2) sum = (num1[l1-i-1] - '0') + carry;
            else sum = (num1[l1-i-1]-'0') + (num2[l2-i-1]-'0') + carry;
            carry = sum / 10;
            sum %= 10;
            result[l-i-1] = sum + '0';
         }
         if(carry == 1) result = '1' + result;
         return result;
    }
};

// A better solution by multiplying string to each integer number, and adding the result together. The key is function:
// string multiply(const string& num, int d)

class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        string result = "0";
        if(num1.size() < num2.size()) num1.swap(num2); //longer one first
        int l1 = num1.size(), l2 = num2.size();
        for(int i = 0; i < l2; ++i) {
            string prod = multiply(num1, num2[l2-i-1]-'0');
            prod.append(i, '0');
            result = add(prod, result);
        }
        return result;
    }
    
    string num2str(int num) {
        if(num == 0) return "0";
        string result;
        while(num) {
            result = char(num % 10 + '0') + result;
            num /= 10;
        }
        return result;
    }

    string multiply(const string& num, int d) {
        if(d == 0) return "0";
        else if(d == 1) return num;
        int n = num.size();
        string result(n, '0');
        int sum = 0, carry = 0;
        for(int i = 0; i < n; ++i) {
            sum = (num[n-i-1] - '0')*d + carry;
            carry = sum / 10;
            sum %= 10;
            result[n-i-1] = sum + '0';
        }
        if(carry > 0) result = char(carry + '0') + result;
        return result;
    }

    string add(const string& num1, const string& num2) {
        int l1 = num1.size(), l2 = num2.size();
        int l = max(l1, l2);
        string result(l, '0');
        int sum = 0, carry = 0;
        for(int i = 0; i < l; ++i) {
            if(i >= l1) sum = (num2[l2-i-1] - '0') + carry;
            else if(i >= l2) sum = (num1[l1-i-1] - '0') + carry;
            else sum = (num1[l1-i-1]-'0') + (num2[l2-i-1]-'0') + carry;
            carry = sum / 10;
            sum %= 10;
            result[l-i-1] = sum + '0';
         }
         if(carry == 1) result = '1' + result;
         return result;
    }
};

/**************************************************** 
 ***    040,Medium,Combination Sum II 
 ****************************************************/

/*
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:

    All numbers (including target) will be positive integers.
    Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
    The solution set must not contain duplicate combinations.

For example, given candidate set 10,1,2,7,6,1,5 and target 8,
A solution set is:
[1, 7]
[1, 2, 5]
[2, 6]
[1, 1, 6]
*/

// Notice the difference between this and problem 039? Here it is "collection" while 039 is "set", which means that here C can have duplicates.

// Solution 1. Iterative solution. Similar to 039, except need to avoid choosing duplicates again, also should only choose one number once.
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int> > result;
        int n = candidates.size();
        if(n == 0) return result;
        sort(candidates.begin(), candidates.end());
        vector<int> tmp;
        dfs(candidates, 0, target, tmp, result);
        return result;
    }
    void dfs(vector<int>& candidates, int i, int target, vector<int>& tmp, vector<vector<int> >& result) {
        if(target == 0) {
            result.push_back(tmp);
            return;
        }
        int n = candidates.size();
        if(i == n || target < candidates[i]) return;
        tmp.push_back(0);
        //choose any number from i to n.
        for(int j = i; j < n; ++j) {
            if(j > i && candidates[j] == candidates[j-1]) continue; //avoid duplicates
            tmp.back() = candidates[j];
            dfs(candidates, j+1, target-candidates[j], tmp, result); //j+1: choose the number only once.
        }
        tmp.pop_back();
    }
};


/**************************************************** 
 ***    039,Medium,Combination Sum 
 ****************************************************/

/*
Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:

    All numbers (including target) will be positive integers.
    Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
    The solution set must not contain duplicate combinations.

For example, given candidate set 2,3,6,7 and target 7,
A solution set is:
[7]
[2, 2, 3]
*/

// Solution 1. Recursive solution. Need to sort the number first. Use the fact that all numbers are positive, terminate when target < current number.
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int> > result;
        int n = candidates.size();
        if(n == 0) return result;
        sort(candidates.begin(), candidates.end());
        vector<int> tmp;
        dfs(candidates, 0, target, tmp, result);
        return result;
    }
    void dfs(vector<int>& candidates, int i, int target, vector<int>& tmp, vector<vector<int> >& result) {
        int n = candidates.size();
        if(i == n || target < candidates[i]) return;
        tmp.push_back(0);
        //choose any number from i to n.
        for(int j = i; j < n; ++j) {
            tmp.back() = candidates[j];
            if(target == candidates[j]) result.push_back(tmp);
            else dfs(candidates, j, target-candidates[j], tmp, result);
        }
        tmp.pop_back();
    }
};

// Solution 2. An old iterative solution. (faster)
class Solution {
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
		vector<vector<int> > ret;
		if(candidates.empty()) return ret;
		
		vector<int> sorted = sort(candidates);
	
		//maximum possible numbers target/ min(sorted)
		int n = sorted.size();
		int csize = std::ceil(target/sorted[0]); //no zero!
		vector<int> choice(csize, -1); //stores the indices of a solution in sorted array
		int k = 0; // the k-th number
		int sum = 0; // accumulated sum
		while(k >= 0) {
			if(k == csize) { // target > sums
				k--;
				continue;
			}
			if(choice[k] == -1) { //first time for k-th number
				choice[k] = ((k > 0) ? choice[k-1] : 0); //start from same number before
			} else { //not the first time
				int prev = sorted[choice[k]];
				sum -= prev; //remove sum
				choice[k] ++;
			}
		
			if(choice[k] == n) { // searched till the end
			    choice[k] = -1; //reset
				k--;
				continue;
			}
			//found one
			sum += sorted[choice[k]]; //update sum
			
			//sum exceeding or equal to target
			if(sum >= target) {
				if(sum == target) ret.push_back(construct(choice, sorted));
				sum -= sorted[choice[k]];
				choice[k] = -1;
				k--;
			} else { //check next number
				k++;
			}
		}
		return ret;
	}
	
	//construct vector from choices
	vector<int> construct(const vector<int>& choice, const vector<int>& sorted) {
		vector<int> ret;
		for(int j = 0; j < choice.size(); ++j) {
			if(choice[j] != -1) ret.push_back(sorted[choice[j]]);
			else break; //can break if found an invalid -1 entry
		}
	return ret;
	}
	//insertion sort
	vector<int> sort(vector<int>& num) {
		vector<int> sorted = num;
		int n = sorted.size();
		int i, j;
		for(i = 1; i < n; ++i) {
			j = i;
			int key = sorted[j];
			while( j >= 1 && sorted[j-1] > key) {
				sorted[j] = sorted[j-1]; //shift to right by 1
				j--;
			}
			sorted[j] = key;
		}
		return sorted;
	}
};


/**************************************************** 
 ***    035,Medium,Search Insert Position 
 ****************************************************/

/*
Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0
*/

// Binary search. Loop invariant:
// nums[0 .. lo-1] < target, nums[hi+1, n) > target, nums[lo, hi] TBD
// If found, return index. If not found, return position lo, because when out of while loop we have lo=hi+1, and target is between nums[hi] and nums[lo].

class Solution {
    
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int lo(0), hi(n-1), mid(0);
        while(lo <= hi) {
            mid = lo + (hi-lo)/2;
            if(target == nums[mid]) return mid;
            if(target < nums[mid]) hi = mid-1;
            else lo = mid+1;
        }
        return lo;
    }
}; 

/**************************************************** 
 ***    031,Medium,Next Permutation 
 ****************************************************/

/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
*/

/* Solution implementing an algorithm to generate permutation sequence in lexigraphical order
How is lexigraphical order generated?

For the permutations with the same prefix, the following sub permutations should also be in lexigraphical order, e.g.
13245, 13254, 13425, 13452 ... (same prefix 13, then 2,4,5 are permutaed in lexi-order as well).

For a group of numbers, the first one in the lexi-order is the ascending sequence, the last one is the descending sequence.

We scan right to left, if we see a subsequence that is descending, that part is already the last one of its own lexi-order. For example:

1,2,5,4,3. What is next step? Since we finished the last three positions, we need to proccess 2, basically move to the next larger one, 3.
How to find 3 ? we utilize the descending order of array 5,4,3 we search from right to left and find the first element larger than 2, and it will be the next one. We simply swap it with 2, and the resulting array 5,4,2 will still be descending. We need to reverse it to make it ascending (as the first permutation in the new sub-array 2,4,5). Therefore, here is the whole procedure:

1. Find the largest index k such that a[k] < a[k + 1]. If no such index exists, the permutation is the last permutation.
2. Find the largest index l greater than k such that a[k] < a[l].
3. Swap the value of a[k] with that of a[l].
4. Reverse the sequence from a[k + 1] up to and including the final element a[n].

Since the comparisons are strict, we will not perform unecessary swaps in the case of duplicated ent
ries. So the algorithm works for duplicated entries as well.
*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = n-2, l = n-1;
        while(k >= 0 && nums[k] >= nums[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) { //no next, just reverse it to 1st lexi-order
            int i = 0, j = n-1;
            while(i < j) swap(nums[i++], nums[j--]);
            return;
        }
        while(l > k && nums[l] <= nums[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(nums[k], nums[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(nums[i++], nums[j--]);
    }
};


/**************************************************** 
 ***    029,Medium,Divide Two Integers 
 ****************************************************/

/*
Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT. 
*/

// Solution 1. Subtract and bit-wise shift (*2).
// Need to consider overflow cases.
class Solution {
public:
    int divide(int dividend, int divisor) {
        if(divisor == 0) return INT_MAX;
        if(dividend == 0) return 0;
        if(dividend == INT_MIN) {
            if(divisor == -1) return INT_MAX;
            else if(divisor == 1) return INT_MIN;
        }
        long a = dividend, b = divisor;
        bool neg = (a > 0) ^ (b > 0);
        a = abs(a); b = abs(b);
        int result = 0;
        while(a >= b) {
            long x = b, y = 1;
            while(a >= (x << 1)) {
              x <<= 1; y <<= 1;
            }
            a -= x;
            result += y;
        }
        //result <= INT_MAX
        if(neg) result = -result;
        return result;
    }
};

// Solution 2. Similar one.
class Solution {
public:
    int divide(int dividend, int divisor) {
        long a = dividend, b = divisor;
        a = abs(a); b = abs(b);
        bool negative = (dividend < 0) ^ (divisor < 0);
        // a/b
        long x(b), n(1), ret(0);
        while (x <= a) {
            x <<= 1; n <<= 1;
        }
        //x = n*b and > a
        while (a > 0) {
            while(n > 0 && x > a) { x >>=1; n>>=1; }
            // x <= a or n == 1
            if (n == 0)  break;
            else {
                ret += n;
                a -= x;
            }
        }
        if(negative) return (ret <= long(INT_MAX)+1) ? -ret : INT_MAX;
        else return ret <= INT_MAX ? ret : INT_MAX;
    }
};

/**************************************************** 
 ***    024,Medium,Swap Nodes in Pairs 
 ****************************************************/

/*
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution 1. Iterative solution. Use a dummy head and two pointers.

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        //p is tail of processed list part
        ListNode *p = dummy, *q = p->next;
        //swap q and q->next
        while(q && q->next) {
            ListNode *r = q->next;
            q = r->next; //move to next
            r->next = p->next;
            p->next = r;
            p = r->next; //move forward
            p->next = q;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

// Solution 2. Recursive solution.
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *p = head->next, *q = p->next;
        p->next = head;
        head->next = swapPairs(q);
        return p;
    }
};


/**************************************************** 
 ***    022,Medium,Generate Parentheses 
 ****************************************************/

/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()" 
*/

// Recursive solution. backtracking, DFS
// pre-allocate string, pass reference and string index to avoid string copying. Keep track of number of open and close brackets left.

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        if(n < 1) return result;
        string str(2*n, '0');
        dfs(n, n, 0, str, result);
        return result;
    }
    void dfs(int nl, int nr, int i, string& str, vector<string>& result) {
        if(i == str.size()) {
            result.push_back(str);
            return;
        }
        if(nl > 0) {
            str[i] = '(';
            dfs(nl-1, nr, i+1, str, result);
        }
        if(nr > 0 && nl < nr) {
            str[i] = ')';
            dfs(nl, nr-1, i+1, str, result);
        }
    }
};

// Another iterative solution
class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> ret;
		int k(0); //k is the index of current parenthesis
		int nr(0); //number of left and right parenthesis
		string str(2*n, '('); //initially '('
		while(1) {
			int nl = k+1-nr;
			if(k == 2*n) { //reached end of string, add to solution
				ret.push_back(str);
				k--;
				update(str[k], nr);
			} else if (str[k] == 'X') { //exhaust all trials, abandon and retrace
				update(str[k], nr); //reset to '.'
				k--;
				if(k < 0) break; //breaking condition
				update(str[k], nr); //increment last element
			} else if(nr > n || nl > n || nl < nr){ //unbalanced
				update(str[k], nr);
			} else { //normal
				k++;
			}
		}
		return ret;
	}
	void update(char& c, int& nr) {
		if(c == '(') {
			c = ')';
			nr ++;
		} else if(c == ')') {
			c = 'X';
			nr --;
		}	else if(c == 'X') c = '(';
	}
};

/**************************************************** 
 ***    018,Medium,4Sum 
 ****************************************************/

/*
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

    Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
    The solution set must not contain duplicate quadruplets.

    For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

    A solution set is:
    (-1,  0, 0, 1)
    (-2, -1, 1, 2)
    (-2,  0, 0, 2)
*/

// O(n3) solution, need to take care of duplicated entries.
// Also several optimization lines (break/continue).
// Storing partial sums (e.g. nums[n-2] + nums[n-1]) does not reduce run time.

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int> > result;
        vector<int> tmp(4, 0);
        int n = nums.size();
        if(n <= 3) return result;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n-3; ++i) {
            if(i > 0 && nums[i] == nums[i-1]) continue; //avoid duplicates
            if(nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) break;
            if(nums[i] + nums[n-3] + nums[n-2] + nums[n-1] < target) continue;
            for(int j = i+1; j < n-2; ++j) {
                if(j > i+1 && nums[j] == nums[j-1]) continue; //avoid duplicates
                if(nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) break;
                if(nums[i] + nums[j] + nums[n-2] + nums[n-1] < target) continue;
                int k = j+1, l = n-1;
                while(k < l) {
                    int sum = nums[i] + nums[j] + nums[k] + nums[l];
                    if(sum < target) k++;
                    else if(sum > target) l--;
                    else { //equal
                        tmp[0] = nums[i]; tmp[1] = nums[j]; tmp[2] = nums[k]; tmp[3] = nums[l];
                        result.push_back(tmp);
                        k++; l--;
                        while(k < l && nums[k] == nums[k-1]) k++;
                        while(k < l && nums[l] == nums[l+1]) l--;
                    }
                }
            }
        }
        return result;
    }
};

/**************************************************** 
 ***    017,Medium,Letter Combinations of a Phone Number 
 ****************************************************/

/*
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer could be in any order you want. 
*/

// Solution 1. Recursive dfs solution. Use a dict storing the conversion rule. Terminate at i == n.
// A variant is also given where termination is at i == n-1.

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> dict = {"", "", "abc", "def", "ghi", "jkl", "mno", "prqs", "tuv", "wxyz"};
        vector<string> result;
        if(digits.empty()) return result;
        int n = digits.size();
        string tmp(n, '0');
        dfs(digits, 0, dict, tmp, result);
        return result;
    }
    //starting from i-th digits
    void dfs(const string& digits, int i, vector<string>& dict, string& tmp, vector<string>& result) {
        if(i == digits.size()) {
            result.push_back(tmp);
            return;
        }
        int idx = digits[i] - '0';
        //choose among possible characters in dict[idx]
        for(auto c : dict[idx]) {
            tmp[i] = c;
            dfs(digits, i+1, dict, tmp, result);
        }
    }
/*  // simplified dfs routine terminating at i == n-1
    void dfs(const string& digits, int i, vector<string>& dict, string& tmp, vector<string>& result) {
        int idx = digits[i] - '0';
        int n = digits.size();
        //choose among possible characters in dict[idx]
        for(auto c : dict[idx]) {
            tmp[i] = c;
            if(i == n-1) result.push_back(tmp);
            else dfs(digits, i+1, dict, tmp, result);
        }
    }
*/
};


/**************************************************** 
 ***    016,Medium,3Sum Closest 
 ****************************************************/

/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

/// O(n2) solution

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int result = 0;
        int min_diff = INT_MAX;
        int n = nums.size();
        if(n <= 2) return 0;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n-2; ++i) {
            if(i > 1 && nums[i] == nums[i-1]) continue;
            int j = i+1, k = n-1;
            while(j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                int diff = target - sum;
                if(diff == 0) return target;
                else if(diff < 0) k--;
                else j++;
                if(abs(diff) < min_diff) {
                    min_diff = abs(diff);
                    result = sum;
                }
            }
        }
        return result;
    }
};

/**************************************************** 
 ***    015,Medium,3Sum 
 ****************************************************/

/*
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

    Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
    The solution set must not contain duplicate triplets.

    For example, given array S = {-1 0 1 2 -1 -4},

    A solution set is:
    (-1, 0, 1)
    (-1, -1, 2)
*/

/// O(n2) solution
/// Need to consider duplicated entries.
/// Optimization: break if nums[i] > 0, and also num[n-1] < 0 (52ms => 48ms)

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ret;
        int n = nums.size();
        if(n <= 2) return ret;
        vector<int> tmp(3, -1);
        sort(nums.begin(), nums.end());
        if(nums[n-1] < 0) return ret; //no need to continue if largest value is < 0
        for(int i = 0; i < n-2; i++) {
            if(nums[i] > 0) break; //no need to continue if found a positive number
            if(i > 0 && nums[i] == nums[i-1]) continue; //avoid duplicates
            if(nums[i] + nums[i+1] + nums[i+2] > 0) break;
            if(nums[i] + nums[n-2] + nums[n-1] < 0) continue;
            int target = -nums[i];
            int j = i+1, k = n-1;
            while(j < k) {
               int sum = nums[j] + nums[k];
               if(sum < target) j++;
               else if(sum > target) k--;
               else {
                   tmp[0] = nums[i]; tmp[1] = nums[j]; tmp[2] = nums[k];
                   ret.push_back(tmp);
                   j++; k--;
                   while(j < k && nums[j] == nums[j-1]) j++; //avoid duplicates
                   while(j < k && nums[k] == nums[k+1]) k--; //avoid duplicates
               }
            }
        }
        return ret;
    }
};

/// O(n2 lgn) solution. Iterate first 2 brute-force, and use binary search to find 3rd element.
/// Need to avoid duplicated entries. (lines 14 and 16).

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ret;
        
        int n = nums.size();
        if(n <= 2) return ret;
        vector<int> sol(3, 0);
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; ++i) { //whether nums[i] is one of the triplet?
            if(i > 0 && nums[i] == nums[i-1]) continue; //ignore duplicates
            for(int j = i+1; j < n; ++j) {
                if(j > i+1 && nums[j] == nums[j-1]) continue; //ignore duplicates
                int target = -(nums[i] + nums[j]);
                int r = find(nums, j+1, target);
                if(r != -1) {
                    sol[0] = nums[i], sol[1] = nums[j], sol[2] = nums[r];
                    ret.push_back(sol);
                }
            }
        }
        return ret;
    }
    
    //search target in sorted array nums[k..end)
    int find(vector<int>& nums, int k, int target) {
        int lo = k, hi = nums.size()-1;
        while(lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if(target < nums[mid]) hi = mid-1;
            else if(target > nums[mid]) lo = mid+1;
            else return mid;
        }
        return -1;
    }
};

/**************************************************** 
 ***    012,Medium,Integer to Roman 
 ****************************************************/

/*
Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.
*/

// A simple solution using a table

const int values[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
const string strs[13] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        
class Solution {
public:
    string intToRoman(int num) {
        string s;
        for(int i = 0; i < 13; ++i) {
            while(num >= values[i]) {
                num -= values[i];
                s += strs[i];
            }
            if(num == 0) break;
        }
        return s;
    }
};

// An old solution. use an append function. Deal with one, five, ten
class Solution {
public:
    string intToRoman(int num) {
        string s;
        int n = 0;
        if (num >= 1000) { append(s, num/1000, 'M', 'Y', 'Z'); num %= 1000; }
        if (num >= 100)  { append(s, num/100,  'C', 'D', 'M'); num %= 100;  }
        if (num >= 10)   { append(s, num/10,   'X', 'L', 'C'); num %= 10;   }
        if (num >= 1)    { append(s, num/1,    'I', 'V', 'X'); }
        return s;
    }
    //c1 is for one, c2 is for five, c3 is for ten
    void append(string& s, int d, char c1, char c2, char c3) {
        if (d == 0) return;
        else if (d <= 3) s += string(d, c1);
        else if (d == 4) { s += c1; s += c2;  }
        else if (d == 5) s += c2;
        else if (d <= 8) { s += c2; s += string(d-5, c1); }
        else if (d == 9) { s += c1; s += c3; }
    }
};

/**************************************************** 
 ***    011,Medium,Container With Most Water 
 ****************************************************/

/*
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container. 
*/

/*
Similar idea to "trapping rain water". Maintain two pointers and find the minimum water level deterimed by the two pointers. Move from the side with lower height, stop when two pointers meet.
The height of container is the smaller of the two ends. Proceed by moving the lower point inwards, because we can proove that the interval between lo and hi is the widest one possible for the container of height of height[lo].
Proceeding from higher point is wrong! e.g.
height:   3 9 1 1
position: 0 1 2 3

l = 0, h = 3 => area = 3
if we move from higher point, we missed [0, 1] with area 6.
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int area = 0;
        int n = height.size();
        if(n <= 1) return 0;
        int l(0), r(n-1);
        while(l < r) {
            area = max(area, min(height[l], height[r])*(r-l));
            if(height[l] < height[r]) l++;
            else r--;
        }
        return area;
    }
};

/**************************************************** 
 ***    003,Medium,Longest Substring Without Repeating Characters 
 ****************************************************/

/*
Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*/

// Solution 1, use a map to store the position of each character (since s is string, can use an indexed array which is faster than map). Scan from left to right, and maintain a map to store characters already seen and its last position, update length each time.
// Use a pointer (i) to store the current front of substring
// When a character is not in the map, insert it to map; 
// When a character is found and its index is within i and j, then move i to one character to the right of it. 

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> pos(256, -1); //map<char, int> pos;
        int max_len(0);
        for(int i = 0, j = 0; j < s.size(); ++j) {
            char c = s[j];
            if(pos[c] >= i)  i = pos[c]+1;
            pos[c] = j;
            max_len = max(max_len, j-i+1);
        }
        return max_len;
    }
};

// Another solution by counting the occurrences of each character, similar to problem 159.
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
         int n = s.size(); //number of records
         int istart = 0, max_len = 0;
         int count = 0;
         vector<int> dict(256);
         for(int i = 0; i < n; ++i) {
            char c = s[i];
            ++dict[c];
            while(dict[c] > 1) {
               --dict[s[istart++]];
            }
            max_len = max(max_len, i-istart+1);
         }
         return max_len;
    }
};

/**************************************************** 
 ***    002,Medium,Add Two Numbers 
 ****************************************************/

/*
You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Use dummy head. Add additional node if final carry = 1.
// Caveats:
// 1. Don't forget to move l1 and l2 forward!
// 2. Last step, scheck if carry > 0, not carry > 1 !

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0), *p(dummy);
        int sum = 0, carry = 0;
        while(l1 || l2) {
            int v1 = l1 ? l1->val : 0;
            int v2 = l2 ? l2->val : 0;
            sum = v1 + v2 + carry;
            carry = sum / 10;
            sum %= 10;
            p->next = new ListNode(sum);
            p = p->next;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        if(carry > 0) p->next = new ListNode(carry);
        
        p = dummy->next;
        delete dummy;
        return p;
    }
};



/**************************************************** 
 ***    001,Medium,Two Sum 
 ****************************************************/

/*
Given an array of integers, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/

// This solution uses a map to store the positions of each number in array. Uses two passes, first pass builds the map, second pass do the two-sum check. For each number if the other number is in then found.
// There is a simpler way to do this, see solution 2.

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        map<int, int> s; //occurrence index
        vector<int> ret(2, 0);
        int n = numbers.size();
        if(n == 0) return ret;
        //build hash table first
        for(int k = 0; k < n; ++k)  s[numbers[k]] = k;
        //another sweep
        for(int k = 0; k < n; ++k) { 
            //find residue in map
            map<int, int>::iterator it = s.find(target-numbers[k]);
            if(it != s.end() && it->second != k) { //found and not the same entry
                ret[0] = k+1;  ret[1] = it->second+1;
                break;
            }
        }
        return ret;
    }
};

// This solution uses a map to store the positions of each number in array. Only one pass is needed.
// For each number in the array, see if the residue (target - number) already exists in the map, if yes then found; if no, then add it to map
// This also properly handles duplicates, because checking residue happens before insertion. 
// Unordered map (hash table) is faster than map (which is balanced tree) in this case.

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
      unordered_map<int, int> table;
      vector<int> ret(2, -1);
      int n = nums.size();
      for(int i = 0; i < nums.size(); i++) {
        int res = target - nums[i];
        if(table.count(res)) {
           ret[0] = table[res]+1; ret[1] = i+1;
           break;
        } else {
           table[nums[i]] = i;
        }
      }
      return ret;
    }
};

// This version uses insertion sort t sort nums, together with its positions as satellite data. Use two pointers to find the 
// target items, and return their positions. (No hash table is involved)
// Insertion sort: O(n2), search for target: O(n).
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> pos(n);
        for(int i = 0; i < n; ++i) pos[i] = i+1;
        //insertion sort nums
        for(int i = 1; i < n; ++i) {
            int tmp = nums[i];
            int tmp2 = pos[i];
            int j = i-1;
            while(j >= 0 && nums[j] > tmp) {
                nums[j+1] = nums[j]; 
                pos[j+1] = pos[j];
                j--;
            }
            nums[j+1] = tmp;
            pos[j+1] = tmp2;
        }
        
        int l = 0, r = nums.size()-1;
        vector<int> ret(2, 0);
        while(1) {
            int sum = nums[l] + nums[r];
            if(target == sum) {
                ret[0] = min(pos[l], pos[r]), ret[1] = max(pos[l], pos[r]);
                return ret;
            } else if (target > sum) l++;
            else r--;
        }
        return ret;
    }
};


