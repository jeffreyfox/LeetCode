/*
Given a sorted integer array where the range of elements are [lower, upper] inclusive, return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"]. 
*/

// First locate the lower and upper in the array, using binary search.
// Then linearly scan the portion of array that falls into [lower, upper], and check missing ranges.

class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> ret;
        int i(0), j(0);
        int n = nums.size();
        int lo(0), hi(n-1), mid(0);
        //i is first element >= lower
        while(lo <= hi) {
           mid = lo + (hi-lo)/2;
           if(nums[mid] < lower) lo++;
           else hi--;
        }
        i = lo;
        lo = 0, hi = n-1;
        //j is last element <= upper
        while(lo <= hi) {
           mid = lo + (hi-lo)/2;
           if(nums[mid] > upper) hi--;
           else lo++;
        }
        j = hi;

        if(i > j) { //array is outside of [lower, upper]
            appendRange(ret, lower, upper);
            return ret;
        }
        //insert
        appendRange(ret, lower, nums[i]-1);
        for(int k = i; k < j; ++k) {
            appendRange(ret, nums[k]+1, nums[k+1]-1);
        }
        appendRange(ret, nums[j]+1, upper);
        return ret;
    }
    void appendRange(vector<string>& ret, int lo, int hi) {
        if(lo == hi) ret.push_back(num2str(lo));
        else if(lo < hi) ret.push_back(num2str(lo) + "->" + num2str(hi));
    }
    string num2str(int num) {
        if(num == 0) return "0";
        string s;
        int sign = num >= 0 ? 1 : -1;
        num = abs(num);
        while(num) {
            s = char(num%10 + '0') + s;
            num /= 10;
        }
        if(sign < 0) s = "-" + s;
        return s;
    }
};

