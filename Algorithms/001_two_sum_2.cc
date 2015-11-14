/*
Given an array of integers, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/

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
