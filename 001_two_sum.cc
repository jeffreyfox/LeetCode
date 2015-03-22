class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        map<int, int> s; //occurrence index
        vector<int> ret;
        int n = numbers.size();
        if(n == 0) return ret;
        vector<int> numbers_rec(n);
        for(int k = 0; k < n; ++k) { 
            s[numbers[k]] = k;
        }
        for(int k = 0; k < n; ++k) { 
            int val = target - numbers[k];
            map<int, int>::iterator it = s.find(val);
            if(it != s.end() && it->second != k) { //not the same entry
                ret.push_back(k+1);
                ret.push_back(it->second+1);
                break;
            }
        }
        return ret;
    }
};
