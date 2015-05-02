/// O(n2) solution
/// Need to consider duplicated entries. See lines 13, 23, 24.

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
            
            int target = -nums[i];
            int lo = i+1, hi = n-1; //linear search for the other two
           
            //Whether we decremented hi or incremented lo from last step
            bool from_lo = false, from_hi = false;
            
            while(lo < hi) {
                //the next two lines ignors duplicates
                if(from_hi && nums[hi] == nums[hi+1]) { hi--; continue;}
                if(from_lo && nums[lo] == nums[lo-1]) { lo++; continue;}
                
                if(nums[lo] + nums[hi] > target) { hi--; from_hi = true;}
                else if(nums[lo] + nums[hi] < target) { lo++; from_lo = true;}
                else { //equal
                    sol[0] = nums[i], sol[1] = nums[lo], sol[2] = nums[hi];
                    ret.push_back(sol);
                    hi--; //just decrement hi to search next (can also increment lo)
                    from_hi = true;
                }
            }
        }
        return ret;
    }
};
