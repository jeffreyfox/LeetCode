/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.

Hint:

How many majority elements could it possibly have?
*/

// Solution extended from Moore's Voting algortihm
// Caveat: need to count again in the end after we find maj1 and maj2, e.g. [3,2,3]. maj2 will be 2, but 2 is not a majority element.

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        int maj1 = 0, maj2 = 0, count1 = 0, count2 = 0;
        int nmaj = 0;
        for(auto x : nums) {
            if(nmaj == 0) { nmaj = 1; maj1 = x; count1 = 1; }
            else if(nmaj == 1) { //always maj1 will have the value
                if(x == maj1) count1++;
                else { //x != maj1
                    nmaj = 2;
                    maj2 = x; count2 = 1;
                }
            } else { //already have 2 majs
                if(x == maj1) count1++;
                else if(x == maj2) count2++;
                else {
                    count1--;
                    count2--;
                    if(count1 == 0) nmaj--;
                    if(count2 == 0) nmaj--;
                    if(count1 == 0 && count2 != 0) {
                        count1 = count2;
                        maj1 = maj2;
                    }
                }
            }
        }
        vector<int> result;
        //count again
        count1 = 0; count2 = 0;
        for(auto x : nums) {
            if(x == maj1) count1++;
            else if(x == maj2) count2++;
        }
        if(count1 > n/3) result.push_back(maj1);
        if(count2 > n/3) result.push_back(maj2);
        return result;
    }
};
