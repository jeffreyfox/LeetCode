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
