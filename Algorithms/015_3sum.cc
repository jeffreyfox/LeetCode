/// O(n2) solution
/// Need to consider duplicated entries. See lines 14 and 27.

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ret;
        int n = nums.size();
        if(n <= 2) return ret;
        vector<int> sol(3, 0);
        sort(nums.begin(), nums.end());
        
        for(int i = 0; i < n; ++i) { //whether nums[i] is one of the triplet?
            if(i > 0 && nums[i] == nums[i-1]) continue; //ignore duplicates
            
            int res = -nums[i];
            int lo = i+1, hi = n-1; //linear search for the other two
           
            while(lo < hi) {
                
                if(nums[lo] + nums[hi] > res) hi--;
                else if(nums[lo] + nums[hi] < res) lo++;
                else { //equal
                    sol[0] = nums[i], sol[1] = nums[lo], sol[2] = nums[hi];
                    ret.push_back(sol);
                    hi--; //just decrement hi to search next (can also increment lo)
                    while(lo < hi && nums[hi] == nums[hi+1]) hi--; //avoid duplicates
                }
            }
        }
        return ret;
    }
};

