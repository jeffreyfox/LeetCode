/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Find all strobogrammatic numbers that are of length = n.

For example,
Given n = 2, return ["11","69","88","96"]. 
*/

// Solution 1. Recursive. First add solutions with leading zeros and put them in the end of vector. then erase them altogether.

class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        vector<string> result;
        if(n == 1) {
            result = {"0", "1", "8"};
            return result;
        }
        stroboHelper(n, result);
        //remove ones starting with zero
        int i = 0;
        for(i = 0; i < result.size(); ++i) {
            if(result[i][0] == '0') break;
        }
        result.resize(i);
        return result;
    }
    void stroboHelper(int n, vector<string>& result) {
        if(n == 1) result = {"1", "8", "0"}; 
        else if(n == 2) result = {"11", "69", "88", "96", "00"};
        else {
            vector<string> tmp;
            stroboHelper(n-2, tmp);
            for(auto it : tmp) {
                result.push_back('1'+it+'1');
                result.push_back('6'+it+'9');
                result.push_back('8'+it+'8');
                result.push_back('9'+it+'6');
            }
            for(auto it : tmp) result.push_back('0'+it+'0');
        }
    }
};

// Solution 2. Iterative. Avoid the annoying leading 0 issue by checking whether reaching last step.

class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        if(n <= 0) return vector<string>();
        if(n == 1) return {"0", "1", "8"};
        if(n == 2) return {"11", "69", "88", "96"};
        vector<string> result;
        if(n % 2 == 1) result = {"0", "1", "8"};
        else result = {"00", "11", "69", "88", "96"};
        vector<string> newresult;
        while(n > 2) {
            n -= 2;
            for(auto it : result) {
                if(n > 2) newresult.push_back('0'+it+'0');
                newresult.push_back('1'+it+'1');
                newresult.push_back('6'+it+'9');
                newresult.push_back('8'+it+'8');
                newresult.push_back('9'+it+'6');
            }
                
            result.swap(newresult);
            newresult.clear();
        }

        return result;
    }
};

