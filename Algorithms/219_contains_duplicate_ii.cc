/// Use a map

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int, int> c;
        for (int i = 0; i < nums.size(); ++i) {
            map<int, int>::iterator it = c.find(nums[i]);
            if (it == c.end()) c[nums[i]] = i; //init last position
            else if (i - it->second <= k) return true; //found!
            else it->second = i; //update last position
        }
        return false;
    }
};
