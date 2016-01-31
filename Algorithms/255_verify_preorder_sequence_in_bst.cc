/*
Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.

You may assume each number in the sequence is unique.

Follow up:
Could you do it using only constant space complexity?
*/

// Solution 1. Using a stack, O(n) space. https://leetcode.com/discuss/51543/java-o-n-and-o-1-extra-space
// when seeing a number smaller than the top of stack, push to stack, otherwise pop all values in the stack smaller than current value.
// Also maintain a lower bound value (lo) that all new values are subject to.

class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        if(preorder.empty()) return true;
        stack<int> s;
        int lo = INT_MIN;
        for(int x : preorder) {
            if(x < lo) return false;
            while(!s.empty() && x > s.top()) {
                lo = s.top(); //update lower bound
                s.pop();
            }
            s.push(x);
        }
        return true;
    }
};

// Solution 2, manipulate original vector as stack, O(1) space. Modifies original vector. i is the top of the stack, when inserting a 
// new value, set the ++i position to the new value.

class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        if(preorder.empty()) return true;
        int i = -1;
        int lo = INT_MIN;
        for(int x : preorder) {
            if(x < lo) return false;
            while(i != -1 && x > preorder[i]) {
                lo = preorder[i]; //update lower bound
                i--;
            }
            preorder[++i] = x;
        }
        return true;
    }
};

// Solution 3, recursive solution, very slow. Idea is to first locate root (first element), then locate left and right subtree.
// Start of right subtree starts at the first element larger than root value. Then recursively check left and right subtree.
// The proper lower and higher bounds need to be maintained.
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        if(preorder.empty()) return true;
     //   long lo = long(INT_MIN)-1, hi = long(INT_MAX)+1;
        int lo = INT_MIN, hi = INT_MAX;
        return verify(preorder, 0, preorder.size()-1, lo, hi);
    }
    //check whether pre[i .. j] is between [lo .. hi]
    bool verify(vector<int>& preorder, int i, int j, int lo, int hi) {
        if(i > j) return true; //empty
        int root_val = preorder[i];
        if(root_val < lo || root_val > hi) return false;
        int k = i+1;
        while(k <= j && preorder[k] < root_val) k++;
        //k points to start of right subtree or end of preorder
        return verify(preorder, i+1, k-1, lo, root_val) && verify(preorder, k, j, root_val, hi);
    }
};

