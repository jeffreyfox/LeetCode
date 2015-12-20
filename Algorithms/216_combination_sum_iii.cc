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


