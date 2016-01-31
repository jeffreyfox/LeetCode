/*
Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.
*/

// Solution using Moore's Voting Algorithm

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        int maj = 0, count = 0;
        for(auto x : nums) {
            if(count == 0) { maj = x; count++; }
            else if(x == maj) count++;
            else count--;
        }
        return maj;
    }
};

