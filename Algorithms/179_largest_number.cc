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
