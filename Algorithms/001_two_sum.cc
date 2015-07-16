class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        map<int, int> s; //occurrence index
        vector<int> ret(2, 0);
        int n = numbers.size();
        if(n == 0) return ret;
        //build hash table first
        for(int k = 0; k < n; ++k)  s[numbers[k]] = k;
        //another sweep
        for(int k = 0; k < n; ++k) { 
            //find residue in map
            map<int, int>::iterator it = s.find(target-numbers[k]);
            if(it != s.end() && it->second != k) { //found and not the same entry
                ret[0] = k+1;  ret[1] = it->second+1;
                break;
            }
        }
        return ret;
    }
};
