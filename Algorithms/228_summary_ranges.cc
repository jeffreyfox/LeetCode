/*
Given a sorted integer array without duplicates, return the summary of its ranges.

For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"]. 
*/

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
        if (n == 0) return "0";
        int sign = (n > 0) ? 1 : -1;
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

//Another solution using one while loop.
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> result;
        if(nums.empty()) return result;
        int l = nums[0];
        int i = 0, n = nums.size();
        while(i < n) {
            if(i+1 == n || nums[i+1] > nums[i]+1)  { // nums[i] is the boundary
                result.push_back(getRange(l, nums[i]));
                if(i+1 < n) l = nums[i+1];
            }
            i++;
        }
        return result;
    }

    string getRange(int l, int r) {
        if(l == r) return num2str(l);
        else return num2str(l) + "->" + num2str(r);
    }
    string num2str(long n) {
        if(n == 0) return "0";
        bool neg = (n < 0);
        n = abs(n);
        string s;
        while(n) {
            s = char(n % 10 + '0') + s;
            n /= 10;
        }
        if(neg) s = "-" + s;
        return s;
    }
};

