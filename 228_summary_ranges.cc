// two pointers
// be careful of overflow when converting from number to string (use unsigned int to store absolute value of an int is ok)

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ret;
        int n = nums.size();
        int i(0), j(0);
        
        while (i < n && j < n) {
            j = i+1;
            while (j < n && nums[j] == nums[j-1]+1) j++;
            //j stops at one past end
            if (j-1 == i) ret.push_back(num2str(nums[i]));
            else ret.push_back(num2str(nums[i]) + "->" + num2str(nums[j-1]));
            i = j;
        }
        return ret;
    }
    string num2str(int n) {
        int sign = (n >= 0) ? 1 : -1;
        if (n == 0) return "0";
        unsigned u = abs(n);
        string s;
        while (u) {
            char c = u % 10 + '0';
            s = c + s;
            u = u / 10;
        }
        if (sign < 0) s = '-' + s;
        return s;
    }
};

